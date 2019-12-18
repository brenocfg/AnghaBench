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
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int server_count ; 
 int /*<<< orphan*/ * serverp ; 

__attribute__((used)) static ip_addr_t* get_free_server() {
  ip_addr_t* temp = (ip_addr_t *) malloc((server_count + 1) * sizeof(ip_addr_t));

  if (server_count > 0) {
    memcpy(temp, serverp, server_count * sizeof(ip_addr_t));
  }
  if (serverp) {
    free(serverp);
  }
  serverp = temp;

  return serverp + server_count;
}