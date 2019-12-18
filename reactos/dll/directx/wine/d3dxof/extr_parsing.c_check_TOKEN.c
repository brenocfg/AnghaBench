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
struct TYPE_4__ {int /*<<< orphan*/  current_token; scalar_t__ token_present; } ;
typedef  TYPE_1__ parse_buffer ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  parse_TOKEN (TYPE_1__*) ; 

__attribute__((used)) static WORD check_TOKEN(parse_buffer * buf)
{
  if (buf->token_present)
    return buf->current_token;

  buf->current_token = parse_TOKEN(buf);
  buf->token_present = TRUE;

  return buf->current_token;
}