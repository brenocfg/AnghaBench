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
struct output_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_byte (struct output_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_data(void *user_ptr, void *user_data, int length)
{
    unsigned char *data = user_data;
    struct output_stream *out = user_ptr;
    int len = length;

    while (len-- > 0)
    {
        if (!write_byte(out, *data++)) return 0;
    }

    return length;
}