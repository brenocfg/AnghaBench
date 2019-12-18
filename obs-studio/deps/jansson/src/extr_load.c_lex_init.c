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
struct TYPE_3__ {size_t flags; int /*<<< orphan*/  token; int /*<<< orphan*/  saved_text; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ lex_t ;
typedef  int /*<<< orphan*/  get_func ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_INVALID ; 
 scalar_t__ strbuffer_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int lex_init(lex_t *lex, get_func get, size_t flags, void *data)
{
    stream_init(&lex->stream, get, data);
    if(strbuffer_init(&lex->saved_text))
        return -1;

    lex->flags = flags;
    lex->token = TOKEN_INVALID;
    return 0;
}