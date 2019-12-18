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
struct symbol {int dummy; } ;
struct string_list {int dummy; } ;
typedef  enum symbol_type { ____Placeholder_symbol_type } symbol_type ;

/* Variables and functions */
 struct symbol* __add_symbol (char const*,int,struct string_list*,int,int) ; 

__attribute__((used)) static struct symbol *add_reference_symbol(const char *name, enum symbol_type type,
				    struct string_list *defn, int is_extern)
{
	return __add_symbol(name, type, defn, is_extern, 1);
}