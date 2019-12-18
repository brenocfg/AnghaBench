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
struct TYPE_4__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ lex_t ;
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 int STREAM_STATE_EOF ; 
 int STREAM_STATE_ERROR ; 
 int /*<<< orphan*/  lex_save (TYPE_1__*,int) ; 
 int stream_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lex_get_save(lex_t *lex, json_error_t *error)
{
    int c = stream_get(&lex->stream, error);
    if(c != STREAM_STATE_EOF && c != STREAM_STATE_ERROR)
        lex_save(lex, c);
    return c;
}