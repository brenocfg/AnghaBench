#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_9__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct plugind {int enabled; void* started_t; int /*<<< orphan*/  cmd; int /*<<< orphan*/  fullfilename; int /*<<< orphan*/  filename; int /*<<< orphan*/  id; int /*<<< orphan*/ * next; int /*<<< orphan*/  obsolete; int /*<<< orphan*/  successful_collections; int /*<<< orphan*/  serial_failures; int /*<<< orphan*/  pid; int /*<<< orphan*/  update_every; } ;
struct TYPE_11__ {int /*<<< orphan*/  machine_guid; } ;
struct TYPE_10__ {char const* hostname; char const* machine_guid; scalar_t__ connected_senders; scalar_t__ health_enabled; void* senders_disconnected_time; void* health_delay_up_to; } ;
typedef  int /*<<< orphan*/  RRD_MEMORY_MODE ;
typedef  int RRDPUSH_MULTIPLE_CONNECTIONS_STRATEGY ;
typedef  TYPE_1__ RRDHOST ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CONFIG_BOOLEAN_AUTO ; 
 int CONFIG_BOOLEAN_NO ; 
 int /*<<< orphan*/  CONFIG_MAX_NAME ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  PLUGINSD_CMD_MAX ; 
 int /*<<< orphan*/  RRDHOST_FLAG_ORPHAN ; 
#define  RRDPUSH_MULTIPLE_CONNECTIONS_ALLOW 129 
#define  RRDPUSH_MULTIPLE_CONNECTIONS_DENY_NEW 128 
 int /*<<< orphan*/  START_STREAMING_PROMPT ; 
 char* appconfig_get (int /*<<< orphan*/ *,char const*,char*,char*) ; 
 int appconfig_get_boolean (int /*<<< orphan*/ *,char const*,char*,int) ; 
 int appconfig_get_boolean_ondemand (int /*<<< orphan*/ *,char const*,char*,int) ; 
 int appconfig_get_number (int /*<<< orphan*/ *,char const*,char*,int) ; 
 char* appconfig_set_default (int /*<<< orphan*/ *,char const*,char*,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int default_health_enabled ; 
 int default_rrd_history_entries ; 
 int /*<<< orphan*/  default_rrd_memory_mode ; 
 int /*<<< orphan*/  default_rrd_update_every ; 
 char* default_rrdpush_api_key ; 
 char* default_rrdpush_destination ; 
 int default_rrdpush_enabled ; 
 char* default_rrdpush_send_charts_matching ; 
 int /*<<< orphan*/  error (char*,char const*,char*,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int get_multiple_connections_strategy (int /*<<< orphan*/ *,char const*,char*,int) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 TYPE_9__* localhost ; 
 int /*<<< orphan*/  log_stream_connection (char*,char*,char const*,char const*,char const*,char*) ; 
 void* now_realtime_sec () ; 
 size_t pluginsd_process (TYPE_1__*,struct plugind*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rrd_memory_mode_id (char*) ; 
 char* rrd_memory_mode_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* rrdhost_find_or_create (char const*,char const*,char const*,char const*,char const*,char const*,char const*,char const*,int,int,int /*<<< orphan*/ ,unsigned int,unsigned int,char*,char*,char*) ; 
 int /*<<< orphan*/  rrdhost_flag_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdhost_flag_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdhost_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdhost_wrlock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdpush_sender_thread_stop (TYPE_1__*) ; 
 scalar_t__ send_timeout (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintfz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ sock_delnonblock (int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_config ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rrdpush_receive(int fd
                           , const char *key
                           , const char *hostname
                           , const char *registry_hostname
                           , const char *machine_guid
                           , const char *os
                           , const char *timezone
                           , const char *tags
                           , const char *program_name
                           , const char *program_version
                           , int update_every
                           , char *client_ip
                           , char *client_port
) {
    RRDHOST *host;
    int history = default_rrd_history_entries;
    RRD_MEMORY_MODE mode = default_rrd_memory_mode;
    int health_enabled = default_health_enabled;
    int rrdpush_enabled = default_rrdpush_enabled;
    char *rrdpush_destination = default_rrdpush_destination;
    char *rrdpush_api_key = default_rrdpush_api_key;
    char *rrdpush_send_charts_matching = default_rrdpush_send_charts_matching;
    time_t alarms_delay = 60;
    RRDPUSH_MULTIPLE_CONNECTIONS_STRATEGY rrdpush_multiple_connections_strategy = RRDPUSH_MULTIPLE_CONNECTIONS_ALLOW;

    update_every = (int)appconfig_get_number(&stream_config, machine_guid, "update every", update_every);
    if(update_every < 0) update_every = 1;

    history = (int)appconfig_get_number(&stream_config, key, "default history", history);
    history = (int)appconfig_get_number(&stream_config, machine_guid, "history", history);
    if(history < 5) history = 5;

    mode = rrd_memory_mode_id(appconfig_get(&stream_config, key, "default memory mode", rrd_memory_mode_name(mode)));
    mode = rrd_memory_mode_id(appconfig_get(&stream_config, machine_guid, "memory mode", rrd_memory_mode_name(mode)));

    health_enabled = appconfig_get_boolean_ondemand(&stream_config, key, "health enabled by default", health_enabled);
    health_enabled = appconfig_get_boolean_ondemand(&stream_config, machine_guid, "health enabled", health_enabled);

    alarms_delay = appconfig_get_number(&stream_config, key, "default postpone alarms on connect seconds", alarms_delay);
    alarms_delay = appconfig_get_number(&stream_config, machine_guid, "postpone alarms on connect seconds", alarms_delay);

    rrdpush_enabled = appconfig_get_boolean(&stream_config, key, "default proxy enabled", rrdpush_enabled);
    rrdpush_enabled = appconfig_get_boolean(&stream_config, machine_guid, "proxy enabled", rrdpush_enabled);

    rrdpush_destination = appconfig_get(&stream_config, key, "default proxy destination", rrdpush_destination);
    rrdpush_destination = appconfig_get(&stream_config, machine_guid, "proxy destination", rrdpush_destination);

    rrdpush_api_key = appconfig_get(&stream_config, key, "default proxy api key", rrdpush_api_key);
    rrdpush_api_key = appconfig_get(&stream_config, machine_guid, "proxy api key", rrdpush_api_key);

    rrdpush_multiple_connections_strategy = get_multiple_connections_strategy(&stream_config, key, "multiple connections", rrdpush_multiple_connections_strategy);
    rrdpush_multiple_connections_strategy = get_multiple_connections_strategy(&stream_config, machine_guid, "multiple connections", rrdpush_multiple_connections_strategy);

    rrdpush_send_charts_matching = appconfig_get(&stream_config, key, "default proxy send charts matching", rrdpush_send_charts_matching);
    rrdpush_send_charts_matching = appconfig_get(&stream_config, machine_guid, "proxy send charts matching", rrdpush_send_charts_matching);

    tags = appconfig_set_default(&stream_config, machine_guid, "host tags", (tags)?tags:"");
    if(tags && !*tags) tags = NULL;

    if (strcmp(machine_guid, localhost->machine_guid) == 0) {
        log_stream_connection(client_ip, client_port, key, machine_guid, hostname, "DENIED - ATTEMPT TO RECEIVE METRICS FROM MACHINE_GUID IDENTICAL TO MASTER");
        error("STREAM %s [receive from %s:%s]: denied to receive metrics, machine GUID [%s] is my own. Did you copy the master/proxy machine guid to a slave?", hostname, client_ip, client_port, machine_guid);
        close(fd);
        return 1;
    }
    else
        host = rrdhost_find_or_create(
                hostname
                , registry_hostname
                , machine_guid
                , os
                , timezone
                , tags
                , program_name
                , program_version
                , update_every
                , history
                , mode
                , (unsigned int)(health_enabled != CONFIG_BOOLEAN_NO)
                , (unsigned int)(rrdpush_enabled && rrdpush_destination && *rrdpush_destination && rrdpush_api_key && *rrdpush_api_key)
                , rrdpush_destination
                , rrdpush_api_key
                , rrdpush_send_charts_matching
        );

    if(!host) {
        close(fd);
        log_stream_connection(client_ip, client_port, key, machine_guid, hostname, "FAILED - CANNOT ACQUIRE HOST");
        error("STREAM %s [receive from [%s]:%s]: failed to find/create host structure.", hostname, client_ip, client_port);
        return 1;
    }

#ifdef NETDATA_INTERNAL_CHECKS
    info("STREAM %s [receive from [%s]:%s]: client willing to stream metrics for host '%s' with machine_guid '%s': update every = %d, history = %ld, memory mode = %s, health %s, tags '%s'"
         , hostname
         , client_ip
         , client_port
         , host->hostname
         , host->machine_guid
         , host->rrd_update_every
         , host->rrd_history_entries
         , rrd_memory_mode_name(host->rrd_memory_mode)
         , (health_enabled == CONFIG_BOOLEAN_NO)?"disabled":((health_enabled == CONFIG_BOOLEAN_YES)?"enabled":"auto")
         , host->tags?host->tags:""
    );
#endif // NETDATA_INTERNAL_CHECKS

    struct plugind cd = {
            .enabled = 1,
            .update_every = default_rrd_update_every,
            .pid = 0,
            .serial_failures = 0,
            .successful_collections = 0,
            .obsolete = 0,
            .started_t = now_realtime_sec(),
            .next = NULL,
    };

    // put the client IP and port into the buffers used by plugins.d
    snprintfz(cd.id,           CONFIG_MAX_NAME,  "%s:%s", client_ip, client_port);
    snprintfz(cd.filename,     FILENAME_MAX,     "%s:%s", client_ip, client_port);
    snprintfz(cd.fullfilename, FILENAME_MAX,     "%s:%s", client_ip, client_port);
    snprintfz(cd.cmd,          PLUGINSD_CMD_MAX, "%s:%s", client_ip, client_port);

    info("STREAM %s [receive from [%s]:%s]: initializing communication...", host->hostname, client_ip, client_port);
    if(send_timeout(fd, START_STREAMING_PROMPT, strlen(START_STREAMING_PROMPT), 0, 60) != strlen(START_STREAMING_PROMPT)) {
        log_stream_connection(client_ip, client_port, key, host->machine_guid, host->hostname, "FAILED - CANNOT REPLY");
        error("STREAM %s [receive from [%s]:%s]: cannot send ready command.", host->hostname, client_ip, client_port);
        close(fd);
        return 0;
    }

    // remove the non-blocking flag from the socket
    if(sock_delnonblock(fd) < 0)
        error("STREAM %s [receive from [%s]:%s]: cannot remove the non-blocking flag from socket %d", host->hostname, client_ip, client_port, fd);

    // convert the socket to a FILE *
    FILE *fp = fdopen(fd, "r");
    if(!fp) {
        log_stream_connection(client_ip, client_port, key, host->machine_guid, host->hostname, "FAILED - SOCKET ERROR");
        error("STREAM %s [receive from [%s]:%s]: failed to get a FILE for FD %d.", host->hostname, client_ip, client_port, fd);
        close(fd);
        return 0;
    }

    rrdhost_wrlock(host);
    if(host->connected_senders > 0) {
        switch(rrdpush_multiple_connections_strategy) {
            case RRDPUSH_MULTIPLE_CONNECTIONS_ALLOW:
                info("STREAM %s [receive from [%s]:%s]: multiple streaming connections for the same host detected. If multiple netdata are pushing metrics for the same charts, at the same time, the result is unexpected.", host->hostname, client_ip, client_port);
                break;

            case RRDPUSH_MULTIPLE_CONNECTIONS_DENY_NEW:
                rrdhost_unlock(host);
                log_stream_connection(client_ip, client_port, key, host->machine_guid, host->hostname, "REJECTED - ALREADY CONNECTED");
                info("STREAM %s [receive from [%s]:%s]: multiple streaming connections for the same host detected. Rejecting new connection.", host->hostname, client_ip, client_port);
                fclose(fp);
                return 0;
        }
    }

    rrdhost_flag_clear(host, RRDHOST_FLAG_ORPHAN);
    host->connected_senders++;
    host->senders_disconnected_time = 0;
    if(health_enabled != CONFIG_BOOLEAN_NO) {
        if(alarms_delay > 0) {
            host->health_delay_up_to = now_realtime_sec() + alarms_delay;
            info("Postponing health checks for %ld seconds, on host '%s', because it was just connected."
            , alarms_delay
            , host->hostname
            );
        }
    }
    rrdhost_unlock(host);

    // call the plugins.d processor to receive the metrics
    info("STREAM %s [receive from [%s]:%s]: receiving metrics...", host->hostname, client_ip, client_port);
    log_stream_connection(client_ip, client_port, key, host->machine_guid, host->hostname, "CONNECTED");

    size_t count = pluginsd_process(host, &cd, fp, 1);

    log_stream_connection(client_ip, client_port, key, host->machine_guid, host->hostname, "DISCONNECTED");
    error("STREAM %s [receive from [%s]:%s]: disconnected (completed %zu updates).", host->hostname, client_ip, client_port, count);

    rrdhost_wrlock(host);
    host->senders_disconnected_time = now_realtime_sec();
    host->connected_senders--;
    if(!host->connected_senders) {
        rrdhost_flag_set(host, RRDHOST_FLAG_ORPHAN);
        if(health_enabled == CONFIG_BOOLEAN_AUTO)
            host->health_enabled = 0;
    }
    rrdhost_unlock(host);

    if(host->connected_senders == 0)
        rrdpush_sender_thread_stop(host);

    // cleanup
    fclose(fp);

    return (int)count;
}