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
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 int /*<<< orphan*/  add_assoc_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
describe_dict_fn (const char * const lang,
                  const char * const name,
                  const char * const desc,
                  const char * const file,
                  void * ud) /* {{{ */
{
	zval *zdesc = (zval *) ud;
	array_init(zdesc);
	add_assoc_string(zdesc, "lang", (char *)lang);
	add_assoc_string(zdesc, "name", (char *)name);
	add_assoc_string(zdesc, "desc", (char *)desc);
	add_assoc_string(zdesc, "file", (char *)file);
}