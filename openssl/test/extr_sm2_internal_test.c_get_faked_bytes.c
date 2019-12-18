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
struct TYPE_2__ {int (* bytes ) (unsigned char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_size_t_le (int,int /*<<< orphan*/ ) ; 
 unsigned char* fake_rand_bytes ; 
 int fake_rand_bytes_offset ; 
 int /*<<< orphan*/  fake_rand_size ; 
 TYPE_1__* saved_rand ; 
 int stub1 (unsigned char*,int) ; 

__attribute__((used)) static int get_faked_bytes(unsigned char *buf, int num)
{
    int i;

    if (fake_rand_bytes == NULL)
        return saved_rand->bytes(buf, num);

    if (!TEST_size_t_le(fake_rand_bytes_offset + num, fake_rand_size))
        return 0;

    for (i = 0; i != num; ++i)
        buf[i] = fake_rand_bytes[fake_rand_bytes_offset + i];
    fake_rand_bytes_offset += num;
    return 1;
}