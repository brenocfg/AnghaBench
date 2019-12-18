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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_FLAGS_NO_REGISTER_ALL ; 
 int /*<<< orphan*/  ENGINE_set_RAND (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_init_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  engine_e_rdrand_id ; 
 int /*<<< orphan*/  engine_e_rdrand_name ; 
 int /*<<< orphan*/  rdrand_init ; 
 int /*<<< orphan*/  rdrand_meth ; 

__attribute__((used)) static int bind_helper(ENGINE *e)
{
    if (!ENGINE_set_id(e, engine_e_rdrand_id) ||
        !ENGINE_set_name(e, engine_e_rdrand_name) ||
        !ENGINE_set_flags(e, ENGINE_FLAGS_NO_REGISTER_ALL) ||
        !ENGINE_set_init_function(e, rdrand_init) ||
        !ENGINE_set_RAND(e, &rdrand_meth))
        return 0;

    return 1;
}