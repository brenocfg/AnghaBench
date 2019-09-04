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
struct m_option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char*) ; 
 int bstr_equals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* m_option_print (struct m_option*,void*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static bool compare_values(struct m_option *type, void *a, void *b)
{
    // Since there is no m_option_equals() or anything similar, we convert all
    // values to a common, unambiguous representation - strings.
    char *as = m_option_print(type, a);
    char *bs = m_option_print(type, b);
    bool res = bstr_equals(bstr0(as), bstr0(bs)); // treat as "" on failure
    talloc_free(as);
    talloc_free(bs);
    return res;
}