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
struct userdata {char* url; int depth; } ;
struct mg_mgr {int dummy; } ;
struct mg_connection {struct userdata* user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_handler ; 
 int /*<<< orphan*/  free (struct userdata*) ; 
 struct userdata* malloc (size_t) ; 
 struct mg_connection* mg_connect_http (struct mg_mgr*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 size_t strlen (char const*) ; 
 char* strncpy (struct userdata*,char const*,size_t) ; 

void crawl_page(struct mg_mgr *mgr, const char *url, size_t url_len,
                int depth) {
  struct mg_connection *nc;
  struct userdata *data = malloc(sizeof(struct userdata));

  if (url_len == (size_t) ~0) {
    url_len = strlen(url);
  }

  data->url = strncpy(malloc(url_len + 1), url, url_len);
  data->url[url_len] = '\0';
  data->depth = depth;

  nc = mg_connect_http(mgr, event_handler, url, NULL, NULL);
  if (nc != NULL) {
    nc->user_data = data;
  } else {
    printf("Error connecting to [%s]\n", url);
    free(data);
  }
}