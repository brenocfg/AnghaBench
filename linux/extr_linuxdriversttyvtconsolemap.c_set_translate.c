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
struct vc_data {size_t vc_num; } ;

/* Variables and functions */
 int* inv_translate ; 
 unsigned short** translations ; 

unsigned short *set_translate(int m, struct vc_data *vc)
{
	inv_translate[vc->vc_num] = m;
	return translations[m];
}