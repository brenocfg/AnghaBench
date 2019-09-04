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
struct hist_browser {int (* title ) (struct hist_browser*,char*,size_t) ;} ;

/* Variables and functions */
 int stub1 (struct hist_browser*,char*,size_t) ; 

__attribute__((used)) static int hist_browser__title(struct hist_browser *browser, char *bf, size_t size)
{
	return browser->title ? browser->title(browser, bf, size) : 0;
}