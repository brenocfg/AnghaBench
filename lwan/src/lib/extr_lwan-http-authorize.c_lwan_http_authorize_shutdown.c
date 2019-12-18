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
 int /*<<< orphan*/  cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  realm_password_cache ; 

void lwan_http_authorize_shutdown(void) { cache_destroy(realm_password_cache); }