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
struct TYPE_3__ {int /*<<< orphan*/  saved_text; } ;
typedef  TYPE_1__ lex_t ;

/* Variables and functions */
 int /*<<< orphan*/  strbuffer_append_byte (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void lex_save(lex_t *lex, int c)
{
    strbuffer_append_byte(&lex->saved_text, c);
}