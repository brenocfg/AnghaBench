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
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int MCS_AURQ ; 
 int /*<<< orphan*/  iso_init (int) ; 
 int /*<<< orphan*/  iso_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mcs_send_aurq(void)
{
	STREAM s;

	s = iso_init(1);

	out_uint8(s, (MCS_AURQ << 2));

	s_mark_end(s);
	iso_send(s);
}