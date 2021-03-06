#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ FUNCTION ;

/* Variables and functions */
 unsigned long OPENSSL_LH_strhash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long function_hash(const FUNCTION * a)
{
    return OPENSSL_LH_strhash(a->name);
}