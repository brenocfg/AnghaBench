#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char u_int8_t ;
struct TYPE_6__ {char* haddr; int hlen; } ;
struct interface_info {TYPE_3__ hw_address; TYPE_1__* client; } ;
struct client_config {size_t* requested_options; int /*<<< orphan*/  requested_option_count; TYPE_2__* send_options; } ;
struct TYPE_5__ {char* data; int len; } ;
struct TYPE_4__ {struct client_config* config; } ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int DWORD ;

/* Variables and functions */
 size_t DHO_BROADCAST_ADDRESS ; 
 size_t DHO_DHCP_CLIENT_IDENTIFIER ; 
 size_t DHO_DOMAIN_NAME ; 
 size_t DHO_DOMAIN_NAME_SERVERS ; 
 size_t DHO_HOST_NAME ; 
 size_t DHO_NTP_SERVERS ; 
 size_t DHO_ROUTERS ; 
 size_t DHO_SUBNET_MASK ; 
 size_t DHO_TIME_OFFSET ; 
 int /*<<< orphan*/  GetComputerName (char*,int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAX_COMPUTERNAME_LENGTH ; 
 int /*<<< orphan*/  debug (char*,char*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

int read_client_conf(struct interface_info *ifi) {
       /* What a strange dance */
       struct client_config *config;
       char ComputerName [MAX_COMPUTERNAME_LENGTH + 1];
       LPSTR lpCompName;
       DWORD ComputerNameSize = sizeof ComputerName / sizeof ComputerName[0];

       if ((ifi!= NULL) && (ifi->client->config != NULL))
          config = ifi->client->config;
       else
       {
           warn("util.c read_client_conf poorly implemented!");
           return 0;
       }


       GetComputerName(ComputerName, & ComputerNameSize);
       debug("Hostname: %s, length: %lu",
			   ComputerName, ComputerNameSize);
       /* This never gets freed since it's only called once */
       lpCompName =
       HeapAlloc(GetProcessHeap(), 0, ComputerNameSize + 1);
       if (lpCompName !=NULL) {
           memcpy(lpCompName, ComputerName, ComputerNameSize + 1);
           /* Send our hostname, some dhcpds use this to update DNS */
           config->send_options[DHO_HOST_NAME].data = (u_int8_t*)lpCompName;
           config->send_options[DHO_HOST_NAME].len = ComputerNameSize;
           debug("Hostname: %s, length: %d",
                 config->send_options[DHO_HOST_NAME].data,
                 config->send_options[DHO_HOST_NAME].len);
       } else {
           error("Failed to allocate heap for hostname");
       }
       /* Both Linux and Windows send this */
       config->send_options[DHO_DHCP_CLIENT_IDENTIFIER].data =
             ifi->hw_address.haddr;
       config->send_options[DHO_DHCP_CLIENT_IDENTIFIER].len =
             ifi->hw_address.hlen;

       /* Setup the requested option list */
       config->requested_options
           [config->requested_option_count++] = DHO_SUBNET_MASK;
       config->requested_options
           [config->requested_option_count++] = DHO_BROADCAST_ADDRESS;
       config->requested_options
           [config->requested_option_count++] = DHO_TIME_OFFSET;
       config->requested_options
           [config->requested_option_count++] = DHO_ROUTERS;
       config->requested_options
           [config->requested_option_count++] = DHO_DOMAIN_NAME;
       config->requested_options
           [config->requested_option_count++] = DHO_DOMAIN_NAME_SERVERS;
       config->requested_options
           [config->requested_option_count++] = DHO_HOST_NAME;
       config->requested_options
           [config->requested_option_count++] = DHO_NTP_SERVERS;

       warn("util.c read_client_conf poorly implemented!");
    return 0;
}