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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int coap_start (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int coap_server_listen( lua_State* L )
{
  const char *mt = "coap_server";
  return coap_start(L, mt);
}