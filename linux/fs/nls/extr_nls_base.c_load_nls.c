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
struct nls_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_nls (char*) ; 
 struct nls_table* try_then_request_module (int /*<<< orphan*/ ,char*,char*) ; 

struct nls_table *load_nls(char *charset)
{
	return try_then_request_module(find_nls(charset), "nls_%s", charset);
}