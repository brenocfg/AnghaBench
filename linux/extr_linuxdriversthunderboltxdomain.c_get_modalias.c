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
struct tb_service {char* key; int prtcid; int prtcvers; int prtcrevs; } ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,char*,int,int,int) ; 

__attribute__((used)) static int get_modalias(struct tb_service *svc, char *buf, size_t size)
{
	return snprintf(buf, size, "tbsvc:k%sp%08Xv%08Xr%08X", svc->key,
			svc->prtcid, svc->prtcvers, svc->prtcrevs);
}