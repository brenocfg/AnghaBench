#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mg_str {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mg_mk_str (char*) ; 
 struct mg_str mg_url_encode_opt (struct mg_str const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct mg_str mg_url_encode(const struct mg_str src) {
  return mg_url_encode_opt(src, mg_mk_str("._-$,;~()/"), 0);
}