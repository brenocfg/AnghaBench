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
 unsigned char* PQescapeByteaInternal (int /*<<< orphan*/ *,unsigned char const*,size_t,size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  static_std_strings ; 

unsigned char *
PQescapeBytea(const unsigned char *from, size_t from_length, size_t *to_length)
{
	return PQescapeByteaInternal(NULL, from, from_length, to_length,
								 static_std_strings,
								 false /* can't use hex */ );
}