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
struct hists {int dummy; } ;

/* Variables and functions */
 int __hists__scnprintf_title (struct hists*,char*,size_t,int) ; 

__attribute__((used)) static inline int hists__scnprintf_title(struct hists *hists, char *bf, size_t size)
{
	return __hists__scnprintf_title(hists, bf, size, true);
}