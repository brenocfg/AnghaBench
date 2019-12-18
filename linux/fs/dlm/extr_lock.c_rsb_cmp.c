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
struct dlm_rsb {int /*<<< orphan*/  res_name; } ;

/* Variables and functions */
 int DLM_RESNAME_MAXLEN ; 
 int memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rsb_cmp(struct dlm_rsb *r, const char *name, int nlen)
{
	char maxname[DLM_RESNAME_MAXLEN];

	memset(maxname, 0, DLM_RESNAME_MAXLEN);
	memcpy(maxname, name, nlen);
	return memcmp(r->res_name, maxname, DLM_RESNAME_MAXLEN);
}