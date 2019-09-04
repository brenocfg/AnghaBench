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
typedef  long zip_uint32_t ;
struct zip_string {int /*<<< orphan*/  length; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z_NULL ; 
 scalar_t__ crc32 (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

zip_uint32_t
_zip_string_crc32(const struct zip_string *s)
{
    zip_uint32_t crc;
    
    crc = (zip_uint32_t)crc32(0L, Z_NULL, 0);

    if (s != NULL)    
	crc = (zip_uint32_t)crc32(crc, s->raw, s->length);

    return crc;
}