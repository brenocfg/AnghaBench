#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int etype; } ;

/* Variables and functions */
 int num_supported_enctypes ; 
 TYPE_1__* supported_gss_krb5_enctypes ; 

__attribute__((used)) static int
supported_gss_krb5_enctype(int etype)
{
	int i;
	for (i = 0; i < num_supported_enctypes; i++)
		if (supported_gss_krb5_enctypes[i].etype == etype)
			return 1;
	return 0;
}