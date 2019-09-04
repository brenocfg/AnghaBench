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
struct lcs_card {int /*<<< orphan*/  read; int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int lcs_start_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lcs_stop_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
lcs_start_channels(struct lcs_card *card)
{
	int rc;

	LCS_DBF_TEXT(2, trace, "chstart");
	/* start read channel */
	rc = lcs_start_channel(&card->read);
	if (rc)
		return rc;
	/* start write channel */
	rc = lcs_start_channel(&card->write);
	if (rc)
		lcs_stop_channel(&card->read);
	return rc;
}