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
struct chp_id {int /*<<< orphan*/  id; int /*<<< orphan*/  cssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int chp_get_status (struct chp_id) ; 
 int /*<<< orphan*/  chsc_chp_vary (struct chp_id,int) ; 
 int /*<<< orphan*/  set_chp_logically_online (struct chp_id,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s390_vary_chpid(struct chp_id chpid, int on)
{
	char dbf_text[15];
	int status;

	sprintf(dbf_text, on?"varyon%x.%02x":"varyoff%x.%02x", chpid.cssid,
		chpid.id);
	CIO_TRACE_EVENT(2, dbf_text);

	status = chp_get_status(chpid);
	if (!on && !status)
		return 0;

	set_chp_logically_online(chpid, on);
	chsc_chp_vary(chpid, on);
	return 0;
}