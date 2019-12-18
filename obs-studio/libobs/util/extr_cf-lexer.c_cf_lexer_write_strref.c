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
struct strref {size_t len; int /*<<< orphan*/  array; } ;
struct cf_lexer {scalar_t__* write_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void cf_lexer_write_strref(struct cf_lexer *lex,
					 const struct strref *ref)
{
	strncpy(lex->write_offset, ref->array, ref->len);
	lex->write_offset[ref->len] = 0;
	lex->write_offset += ref->len;
}