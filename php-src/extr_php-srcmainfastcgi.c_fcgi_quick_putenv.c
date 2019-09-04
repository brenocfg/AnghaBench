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
 int /*<<< orphan*/  fcgi_hash_del (int /*<<< orphan*/ *,unsigned int,char*,int) ; 
 char* fcgi_hash_set (int /*<<< orphan*/ *,unsigned int,char*,int,char*,unsigned int) ; 
 scalar_t__ strlen (char*) ; 

char* fcgi_quick_putenv(fcgi_request *req, char* var, int var_len, unsigned int hash_value, char* val)
{
	if (val == NULL) {
		fcgi_hash_del(&req->env, hash_value, var, var_len);
		return NULL;
	} else {
		return fcgi_hash_set(&req->env, hash_value, var, var_len, val, (unsigned int)strlen(val));
	}
}