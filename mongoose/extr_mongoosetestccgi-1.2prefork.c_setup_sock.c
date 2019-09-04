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
struct TYPE_3__ {void* s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {int /*<<< orphan*/  h_length; int /*<<< orphan*/ * h_addr_list; } ;
typedef  int /*<<< orphan*/  local ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 void* INADDR_ANY ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 struct hostent* gethostbyname (char const*) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ inet_aton (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
setup_sock(const char *host, int port) {
    struct sockaddr_in local;
    struct hostent *h;
    int sock;

    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    if (host == 0 || *host == 0) {
        local.sin_addr.s_addr = INADDR_ANY;
    }
    else if (!isdigit(host[0]) ||
        inet_aton(host, &local.sin_addr) == 0)
    {
        if ((h = gethostbyname(host)) != 0) {
            memcpy(&local.sin_addr, h->h_addr_list[0], h->h_length);
        }
        else {
            local.sin_addr.s_addr = INADDR_ANY;
        }
    }
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return sock;
    }
    if (bind(sock, (struct sockaddr *) &local, sizeof(local)) < 0 ||
        listen(sock, 5) < 0)
    {
        close(sock);
        return -1;
    }
    return sock;
}