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
struct TYPE_3__ {scalar_t__ http_major; scalar_t__ http_minor; int flags; } ;
typedef  TYPE_1__ php_http_parser ;

/* Variables and functions */
 int F_CONNECTION_CLOSE ; 
 int F_CONNECTION_KEEP_ALIVE ; 

int
php_http_should_keep_alive (php_http_parser *parser)
{
  if (parser->http_major > 0 && parser->http_minor > 0) {
    /* HTTP/1.1 */
    if (parser->flags & F_CONNECTION_CLOSE) {
      return 0;
    } else {
      return 1;
    }
  } else {
    /* HTTP/1.0 or earlier */
    if (parser->flags & F_CONNECTION_KEEP_ALIVE) {
      return 1;
    } else {
      return 0;
    }
  }
}