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
typedef  int /*<<< orphan*/  t_a ;
typedef  int /*<<< orphan*/  LZ4_stream_t ;

/* Variables and functions */

__attribute__((used)) static size_t LZ4_stream_t_alignment(void)
{
    struct { char c; LZ4_stream_t t; } t_a;
    return sizeof(t_a) - sizeof(t_a.t);
}