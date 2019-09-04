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
struct TYPE_5__ {scalar_t__ value; } ;
typedef  TYPE_1__ token_t ;
struct TYPE_6__ {int noreply; } ;
typedef  TYPE_2__ conn ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static inline bool set_noreply_maybe(conn *c, token_t *tokens, size_t ntokens)
{
    int noreply_index = ntokens - 2;

    /*
      NOTE: this function is not the first place where we are going to
      send the reply.  We could send it instead from process_command()
      if the request line has wrong number of tokens.  However parsing
      malformed line for "noreply" option is not reliable anyway, so
      it can't be helped.
    */
    if (tokens[noreply_index].value
        && strcmp(tokens[noreply_index].value, "noreply") == 0) {
        c->noreply = true;
    }
    return c->noreply;
}