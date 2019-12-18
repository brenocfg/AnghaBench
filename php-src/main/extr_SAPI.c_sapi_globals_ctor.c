#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  known_post_content_types; } ;
typedef  TYPE_1__ sapi_globals_struct ;

/* Variables and functions */
 int /*<<< orphan*/  _type_dtor ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_setup_sapi_content_types () ; 
 int /*<<< orphan*/  zend_hash_init_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sapi_globals_ctor(sapi_globals_struct *sapi_globals)
{
	memset(sapi_globals, 0, sizeof(*sapi_globals));
	zend_hash_init_ex(&sapi_globals->known_post_content_types, 8, NULL, _type_dtor, 1, 0);
	php_setup_sapi_content_types();
}