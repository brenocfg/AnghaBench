#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ci_hdrc {int dummy; } ;
typedef  enum ci_revision { ____Placeholder_ci_revision } ci_revision ;

/* Variables and functions */
 int CI_REVISION_1X ; 
 scalar_t__ CI_REVISION_20 ; 
 int CI_REVISION_UNKNOWN ; 
 int /*<<< orphan*/  ID_ID ; 
 int /*<<< orphan*/  REVISION ; 
 int /*<<< orphan*/  VERSION ; 
 int __ffs (int /*<<< orphan*/ ) ; 
 int hw_read_id_reg (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ci_revision ci_get_revision(struct ci_hdrc *ci)
{
	int ver = hw_read_id_reg(ci, ID_ID, VERSION) >> __ffs(VERSION);
	enum ci_revision rev = CI_REVISION_UNKNOWN;

	if (ver == 0x2) {
		rev = hw_read_id_reg(ci, ID_ID, REVISION)
			>> __ffs(REVISION);
		rev += CI_REVISION_20;
	} else if (ver == 0x0) {
		rev = CI_REVISION_1X;
	}

	return rev;
}