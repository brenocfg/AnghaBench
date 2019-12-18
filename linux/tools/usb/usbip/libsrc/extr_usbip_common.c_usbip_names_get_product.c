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
typedef  int uint16_t ;

/* Variables and functions */
 char* names_product (int,int) ; 
 char* names_vendor (int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char const*,int,int) ; 

void usbip_names_get_product(char *buff, size_t size, uint16_t vendor,
			     uint16_t product)
{
	const char *prod, *vend;

	prod = names_product(vendor, product);
	if (!prod)
		prod = "unknown product";


	vend = names_vendor(vendor);
	if (!vend)
		vend = "unknown vendor";

	snprintf(buff, size, "%s : %s (%04x:%04x)", vend, prod, vendor, product);
}