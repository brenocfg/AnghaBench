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
struct nn_sha1 {int /*<<< orphan*/  bytes_hashed; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_sha1_add (struct nn_sha1*,int /*<<< orphan*/ ) ; 

void nn_sha1_hashbyte (struct nn_sha1 *self, uint8_t data)
{
    ++self->bytes_hashed;
    nn_sha1_add (self, data);
}