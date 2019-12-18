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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SECTION_REGISTRY ; 
 int /*<<< orphan*/  CONFIG_SECTION_WEB ; 
 int /*<<< orphan*/  SIMPLE_PATTERN_EXACT ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_FILTERED ; 
 int /*<<< orphan*/  Z_FIXED ; 
 int /*<<< orphan*/  Z_HUFFMAN_ONLY ; 
 int /*<<< orphan*/  Z_RLE ; 
 void* config_get (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  config_get_boolean (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int config_get_number (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 void* make_dns_decision (int /*<<< orphan*/ ,char*,char*,void*) ; 
 int /*<<< orphan*/  respect_web_browser_do_not_track_policy ; 
 void* simple_pattern_create (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* web_allow_badges_dns ; 
 void* web_allow_badges_from ; 
 void* web_allow_connections_dns ; 
 void* web_allow_connections_from ; 
 void* web_allow_dashboard_dns ; 
 void* web_allow_dashboard_from ; 
 void* web_allow_mgmt_dns ; 
 void* web_allow_mgmt_from ; 
 void* web_allow_netdataconf_dns ; 
 void* web_allow_netdataconf_from ; 
 void* web_allow_registry_dns ; 
 void* web_allow_registry_from ; 
 void* web_allow_streaming_dns ; 
 void* web_allow_streaming_from ; 
 int web_client_first_request_timeout ; 
 int web_client_streaming_rate_t ; 
 int web_client_timeout ; 
 int /*<<< orphan*/  web_enable_gzip ; 
 int web_gzip_level ; 
 int /*<<< orphan*/  web_gzip_strategy ; 
 int /*<<< orphan*/ * web_x_frame_options ; 

void web_server_config_options(void)
{
    web_client_timeout =
        (int)config_get_number(CONFIG_SECTION_WEB, "disconnect idle clients after seconds", web_client_timeout);
    web_client_first_request_timeout =
        (int)config_get_number(CONFIG_SECTION_WEB, "timeout for first request", web_client_first_request_timeout);
    web_client_streaming_rate_t =
        config_get_number(CONFIG_SECTION_WEB, "accept a streaming request every seconds", web_client_streaming_rate_t);

    respect_web_browser_do_not_track_policy =
        config_get_boolean(CONFIG_SECTION_WEB, "respect do not track policy", respect_web_browser_do_not_track_policy);
    web_x_frame_options = config_get(CONFIG_SECTION_WEB, "x-frame-options response header", "");
    if(!*web_x_frame_options)
        web_x_frame_options = NULL;

    web_allow_connections_from =
        simple_pattern_create(config_get(CONFIG_SECTION_WEB, "allow connections from", "localhost *"),
                              NULL, SIMPLE_PATTERN_EXACT);
    web_allow_connections_dns  =
        make_dns_decision(CONFIG_SECTION_WEB, "allow connections by dns", "heuristic", web_allow_connections_from);
    web_allow_dashboard_from   =
        simple_pattern_create(config_get(CONFIG_SECTION_WEB, "allow dashboard from", "localhost *"),
                              NULL, SIMPLE_PATTERN_EXACT);
    web_allow_dashboard_dns    =
        make_dns_decision(CONFIG_SECTION_WEB, "allow dashboard by dns", "heuristic", web_allow_dashboard_from);
    web_allow_badges_from      =
        simple_pattern_create(config_get(CONFIG_SECTION_WEB, "allow badges from", "*"), NULL, SIMPLE_PATTERN_EXACT);
    web_allow_badges_dns       =
        make_dns_decision(CONFIG_SECTION_WEB, "allow badges by dns", "heuristic", web_allow_badges_from);
    web_allow_registry_from    =
        simple_pattern_create(config_get(CONFIG_SECTION_REGISTRY, "allow from", "*"), NULL, SIMPLE_PATTERN_EXACT);
    web_allow_registry_dns     = make_dns_decision(CONFIG_SECTION_REGISTRY, "allow by dns", "heuristic",
                                                   web_allow_registry_from);
    web_allow_streaming_from   = simple_pattern_create(config_get(CONFIG_SECTION_WEB, "allow streaming from", "*"),
                                                       NULL, SIMPLE_PATTERN_EXACT);
    web_allow_streaming_dns    = make_dns_decision(CONFIG_SECTION_WEB, "allow streaming by dns", "heuristic",
                                                   web_allow_streaming_from);
    // Note the default is not heuristic, the wildcards could match DNS but the intent is ip-addresses.
    web_allow_netdataconf_from = simple_pattern_create(config_get(CONFIG_SECTION_WEB, "allow netdata.conf from",
                                                       "localhost fd* 10.* 192.168.* 172.16.* 172.17.* 172.18.*"
                                                       " 172.19.* 172.20.* 172.21.* 172.22.* 172.23.* 172.24.*"
                                                       " 172.25.* 172.26.* 172.27.* 172.28.* 172.29.* 172.30.*"
                                                       " 172.31.*"), NULL, SIMPLE_PATTERN_EXACT);
    web_allow_netdataconf_dns  =
        make_dns_decision(CONFIG_SECTION_WEB, "allow netdata.conf by dns", "no", web_allow_mgmt_from);
    web_allow_mgmt_from        =
        simple_pattern_create(config_get(CONFIG_SECTION_WEB, "allow management from", "localhost"),
                              NULL, SIMPLE_PATTERN_EXACT);
    web_allow_mgmt_dns         =
        make_dns_decision(CONFIG_SECTION_WEB, "allow management by dns","heuristic",web_allow_mgmt_from);


#ifdef NETDATA_WITH_ZLIB
    web_enable_gzip = config_get_boolean(CONFIG_SECTION_WEB, "enable gzip compression", web_enable_gzip);

    char *s = config_get(CONFIG_SECTION_WEB, "gzip compression strategy", "default");
    if(!strcmp(s, "default"))
        web_gzip_strategy = Z_DEFAULT_STRATEGY;
    else if(!strcmp(s, "filtered"))
        web_gzip_strategy = Z_FILTERED;
    else if(!strcmp(s, "huffman only"))
        web_gzip_strategy = Z_HUFFMAN_ONLY;
    else if(!strcmp(s, "rle"))
        web_gzip_strategy = Z_RLE;
    else if(!strcmp(s, "fixed"))
        web_gzip_strategy = Z_FIXED;
    else {
        error("Invalid compression strategy '%s'. Valid strategies are 'default', 'filtered', 'huffman only', 'rle' and 'fixed'. Proceeding with 'default'.", s);
        web_gzip_strategy = Z_DEFAULT_STRATEGY;
    }

    web_gzip_level = (int)config_get_number(CONFIG_SECTION_WEB, "gzip compression level", 3);
    if(web_gzip_level < 1) {
        error("Invalid compression level %d. Valid levels are 1 (fastest) to 9 (best ratio). Proceeding with level 1 (fastest compression).", web_gzip_level);
        web_gzip_level = 1;
    }
    else if(web_gzip_level > 9) {
        error("Invalid compression level %d. Valid levels are 1 (fastest) to 9 (best ratio). Proceeding with level 9 (best compression).", web_gzip_level);
        web_gzip_level = 9;
    }
#endif /* NETDATA_WITH_ZLIB */
}