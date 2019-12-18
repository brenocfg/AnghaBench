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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 double av_int2double (int /*<<< orphan*/ ) ; 
 double av_int2float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebml_parse_uint (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static double ebml_parse_float(uint8_t *data, int length)
{
    assert(length == 0 || length == 4 || length == 8);
    uint64_t i = ebml_parse_uint(data, length);
    if (length == 4)
        return av_int2float(i);
    else
        return av_int2double(i);
}