#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ token; int /*<<< orphan*/  saved_text; } ;
typedef  TYPE_1__ lex_t ;

/* Variables and functions */
 scalar_t__ TOKEN_STRING ; 
 int /*<<< orphan*/  lex_free_string (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuffer_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lex_close(lex_t *lex)
{
    if(lex->token == TOKEN_STRING)
        lex_free_string(lex);
    strbuffer_close(&lex->saved_text);
}