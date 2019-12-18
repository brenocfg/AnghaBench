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
 int /*<<< orphan*/  FCGI_HASH_FUNC (char*,int) ; 
 int /*<<< orphan*/  fcgi_hash_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 char* fcgi_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*,unsigned int) ; 
 scalar_t__ strlen (char*) ; 

char* fcgi_putenv(fcgi_request *req, char* var, int var_len, char* val)
{
	if (!req) return NULL;
	if (val == NULL) {
		fcgi_hash_del(&req->env, FCGI_HASH_FUNC(var, var_len), var, var_len);
		return NULL;
	} else {
		return fcgi_hash_set(&req->env, FCGI_HASH_FUNC(var, var_len), var, var_len, val, (unsigned int)strlen(val));
	}
}