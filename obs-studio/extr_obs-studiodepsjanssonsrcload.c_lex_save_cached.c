#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* buffer; size_t buffer_pos; int /*<<< orphan*/  position; } ;
struct TYPE_6__ {TYPE_1__ stream; } ;
typedef  TYPE_2__ lex_t ;

/* Variables and functions */
 int /*<<< orphan*/  lex_save (TYPE_2__*,char) ; 

__attribute__((used)) static void lex_save_cached(lex_t *lex)
{
    while(lex->stream.buffer[lex->stream.buffer_pos] != '\0')
    {
        lex_save(lex, lex->stream.buffer[lex->stream.buffer_pos]);
        lex->stream.buffer_pos++;
        lex->stream.position++;
    }
}