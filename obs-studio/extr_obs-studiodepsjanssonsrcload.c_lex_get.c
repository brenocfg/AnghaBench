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
struct TYPE_3__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ lex_t ;
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 int stream_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lex_get(lex_t *lex, json_error_t *error)
{
    return stream_get(&lex->stream, error);
}