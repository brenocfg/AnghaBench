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
struct TYPE_3__ {int /*<<< orphan*/  env; } ;
typedef  TYPE_1__ fcgi_request ;

/* Variables and functions */
 int /*<<< orphan*/  FCGI_HASH_FUNC (char const*,int) ; 
 char* fcgi_hash_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,unsigned int*) ; 

char* fcgi_getenv(fcgi_request *req, const char* var, int var_len)
{
	unsigned int val_len;

	if (!req) return NULL;

	return fcgi_hash_get(&req->env, FCGI_HASH_FUNC(var, var_len), (char*)var, var_len, &val_len);
}