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
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_UNSUPPORTED_KEY_SIZE ; 
#define  RC2_128_MAGIC 130 
#define  RC2_40_MAGIC 129 
#define  RC2_64_MAGIC 128 

__attribute__((used)) static int rc2_magic_to_keybits(int magic)
{
    switch (magic) {
    case RC2_128_MAGIC:
        return 128;
    case RC2_64_MAGIC:
        return 64;
    case RC2_40_MAGIC:
        return 40;
    }
    ERR_raise(ERR_LIB_PROV, PROV_R_UNSUPPORTED_KEY_SIZE);
    return 0;
}