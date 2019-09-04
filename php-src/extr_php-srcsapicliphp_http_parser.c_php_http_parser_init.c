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
struct TYPE_3__ {int type; scalar_t__ method; scalar_t__ flags; scalar_t__ upgrade; scalar_t__ nread; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ php_http_parser ;
typedef  enum php_http_parser_type { ____Placeholder_php_http_parser_type } php_http_parser_type ;

/* Variables and functions */
 int PHP_HTTP_REQUEST ; 
 int PHP_HTTP_RESPONSE ; 
 int /*<<< orphan*/  s_start_req ; 
 int /*<<< orphan*/  s_start_req_or_res ; 
 int /*<<< orphan*/  s_start_res ; 

void
php_http_parser_init (php_http_parser *parser, enum php_http_parser_type t)
{
  parser->type = t;
  parser->state = (t == PHP_HTTP_REQUEST ? s_start_req : (t == PHP_HTTP_RESPONSE ? s_start_res : s_start_req_or_res));
  parser->nread = 0;
  parser->upgrade = 0;
  parser->flags = 0;
  parser->method = 0;
}