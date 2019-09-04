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
typedef  int /*<<< orphan*/  vtt_t ;
typedef  int /*<<< orphan*/  utf8_char_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _vtt_parse (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 

vtt_t* vtt_parse(const utf8_char_t* data, size_t size)
{
    return _vtt_parse(data, size, 0);
}