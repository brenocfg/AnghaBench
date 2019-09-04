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

/* Variables and functions */
 int _asn1_check_infinite_end (unsigned char const**,long) ; 

int ASN1_const_check_infinite_end(const unsigned char **p, long len)
{
    return _asn1_check_infinite_end(p, len);
}