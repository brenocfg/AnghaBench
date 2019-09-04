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
typedef  int /*<<< orphan*/  c448_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDDSA_448_PRIVATE_BYTES ; 
 int /*<<< orphan*/  X448_PRIVATE_BYTES ; 
 int /*<<< orphan*/  oneshot_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

c448_error_t c448_ed448_convert_private_key_to_x448(
                            uint8_t x[X448_PRIVATE_BYTES],
                            const uint8_t ed [EDDSA_448_PRIVATE_BYTES])
{
    /* pass the private key through oneshot_hash function */
    /* and keep the first X448_PRIVATE_BYTES bytes */
    return oneshot_hash(x, X448_PRIVATE_BYTES, ed,
                        EDDSA_448_PRIVATE_BYTES);
}