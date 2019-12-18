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
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  buf_write (struct buffer*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rand_bytes (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
random_bytes_to_buf(struct buffer *buf,
                    uint8_t *out,
                    int outlen)
{
    if (!rand_bytes(out, outlen))
    {
        msg(M_FATAL, "ERROR: Random number generator cannot obtain entropy for key generation [SSL]");
    }
    if (!buf_write(buf, out, outlen))
    {
        return false;
    }
    return true;
}