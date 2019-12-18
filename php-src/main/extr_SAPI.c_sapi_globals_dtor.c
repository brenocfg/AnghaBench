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
struct TYPE_3__ {int /*<<< orphan*/  known_post_content_types; } ;
typedef  TYPE_1__ sapi_globals_struct ;

/* Variables and functions */
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sapi_globals_dtor(sapi_globals_struct *sapi_globals)
{
	zend_hash_destroy(&sapi_globals->known_post_content_types);
}