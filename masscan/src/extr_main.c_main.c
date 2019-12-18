#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_11__ {scalar_t__ index; } ;
struct TYPE_9__ {int /*<<< orphan*/  directory; } ;
struct TYPE_10__ {int is_show_open; int is_status_updates; TYPE_3__ rotate; } ;
struct TYPE_8__ {int /*<<< orphan*/  oproto; int /*<<< orphan*/  udp; } ;
struct TYPE_7__ {int one; int of; } ;
struct Masscan {int blackrock_rounds; int wait; double max_rate; int nic_count; int min_packet_size; int is_capture_cert; int is_readscan; int op; TYPE_6__* nic; TYPE_5__ resume; int /*<<< orphan*/  ports; int /*<<< orphan*/  targets; int /*<<< orphan*/  exclude_port; int /*<<< orphan*/  exclude_ip; scalar_t__ is_scripting; TYPE_4__ output; TYPE_2__ payloads; TYPE_1__ shard; int /*<<< orphan*/  seed; } ;
typedef  int /*<<< orphan*/  WSADATA ;
struct TYPE_12__ {int /*<<< orphan*/  ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int,char*) ; 
#define  Operation_Benchmark 136 
#define  Operation_DebugIF 135 
#define  Operation_Default 134 
#define  Operation_ListScan 133 
#define  Operation_List_Adapters 132 
#define  Operation_ReadRange 131 
#define  Operation_ReadScan 130 
#define  Operation_Scan 129 
#define  Operation_Selftest 128 
 int /*<<< orphan*/  WSAStartup (int,int /*<<< orphan*/ *) ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int banner1_selftest () ; 
 int base64_selftest () ; 
 int /*<<< orphan*/  blackrock2_benchmark (int) ; 
 int /*<<< orphan*/  blackrock_benchmark (int) ; 
 int blackrock_selftest () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_entropy () ; 
 int /*<<< orphan*/  global_now ; 
 int lcg_selftest () ; 
 int /*<<< orphan*/  main_listscan (struct Masscan*) ; 
 int /*<<< orphan*/  main_readrange (struct Masscan*) ; 
 int main_scan (struct Masscan*) ; 
 int mainconf_selftest () ; 
 int /*<<< orphan*/  masscan_command_line (struct Masscan*,int,char**) ; 
 scalar_t__ masscan_conf_contains (char*,int,char**) ; 
 int /*<<< orphan*/  masscan_load_database_files (struct Masscan*) ; 
 int /*<<< orphan*/  masscan_read_config_file (struct Masscan*,char*) ; 
 int /*<<< orphan*/  masscan_usage () ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct Masscan*,int /*<<< orphan*/ ,int) ; 
 int nmapserviceprobes_selftest () ; 
 int ntp_selftest () ; 
 int output_selftest () ; 
 int /*<<< orphan*/  payloads_oproto_create () ; 
 int /*<<< orphan*/  payloads_udp_create () ; 
 int payloads_udp_selftest () ; 
 scalar_t__ pcap_init () ; 
 int /*<<< orphan*/  pixie_backtrace_init (char*) ; 
 int /*<<< orphan*/  pixie_gettime () ; 
 int pixie_time_selftest () ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int proto_coap_selftest () ; 
 int rangefile_selftest () ; 
 int rangelist_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rangelist_exclude (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ranges_selftest () ; 
 int /*<<< orphan*/  rawsock_init () ; 
 int /*<<< orphan*/  rawsock_list_adapters () ; 
 int rawsock_selftest () ; 
 int /*<<< orphan*/  rawsock_selftest_if (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_binary_scanfile (struct Masscan*,unsigned int,unsigned int,char**) ; 
 int rstfilter_selftest () ; 
 int rte_ring_selftest () ; 
 int /*<<< orphan*/  scripting_init (struct Masscan*) ; 
 int sctp_selftest () ; 
 int siphash24_selftest () ; 
 int /*<<< orphan*/  smack_benchmark () ; 
 int smack_selftest () ; 
 int /*<<< orphan*/  snmp_init () ; 
 int snmp_selftest () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy_s (int /*<<< orphan*/ ,int,char*) ; 
 int template_selftest () ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usec_start ; 
 int /*<<< orphan*/  x509_init () ; 
 int zeroaccess_selftest () ; 

int main(int argc, char *argv[])
{
    struct Masscan masscan[1];
    unsigned i;
    
    usec_start = pixie_gettime();
#if defined(WIN32)
    {WSADATA x; WSAStartup(0x101, &x);}
#endif

    global_now = time(0);

    /* Set system to report debug information on crash */
    {
        int is_backtrace = 1;
        for (i=1; i<(unsigned)argc; i++) {
            if (strcmp(argv[i], "--nobacktrace") == 0)
                is_backtrace = 0;
        }
        if (is_backtrace)
            pixie_backtrace_init(argv[0]);
    }
    
    /*
     * Initialize those defaults that aren't zero
     */
    memset(masscan, 0, sizeof(*masscan));
    masscan->blackrock_rounds = 4;
    masscan->output.is_show_open = 1; /* default: show syn-ack, not rst */
    masscan->output.is_status_updates = 1; /* default: show status updates */
    masscan->seed = get_entropy(); /* entropy for randomness */
    masscan->wait = 10; /* how long to wait for responses when done */
    masscan->max_rate = 100.0; /* max rate = hundred packets-per-second */
    masscan->nic_count = 1;
    masscan->shard.one = 1;
    masscan->shard.of = 1;
    masscan->min_packet_size = 60;
    masscan->payloads.udp = payloads_udp_create();
    masscan->payloads.oproto = payloads_oproto_create();
    strcpy_s(   masscan->output.rotate.directory,
                sizeof(masscan->output.rotate.directory),
                ".");
    masscan->is_capture_cert = 1;

    /*
     * Pre-parse the command-line
     */
    if (masscan_conf_contains("--readscan", argc, argv)) {
        masscan->is_readscan = 1;
    }

    /*
     * On non-Windows systems, read the defaults from the file in
     * the /etc directory. These defaults will contain things
     * like the output directory, max packet rates, and so on. Most
     * importantly, the master "--excludefile" might be placed here,
     * so that blacklisted ranges won't be scanned, even if the user
     * makes a mistake
     */
#if !defined(WIN32)
    if (!masscan->is_readscan) {
        if (access("/etc/masscan/masscan.conf", 0) == 0) {
            masscan_read_config_file(masscan, "/etc/masscan/masscan.conf");
        }
    }
#endif

    /*
     * Read in the configuration from the command-line. We are looking for
     * either options or a list of IPv4 address ranges.
     */
    masscan_command_line(masscan, argc, argv);
    
    /*
     * Load database files like "nmap-payloads" and "nmap-service-probes"
     */
    masscan_load_database_files(masscan);

    /*
     * Load the scripting engine if needed and run those that were
     * specified.
     */
    if (masscan->is_scripting)
        scripting_init(masscan);

    /* We need to do a separate "raw socket" initialization step. This is
     * for Windows and PF_RING. */
    if (pcap_init() != 0)
        LOG(2, "libpcap: failed to load\n");
    rawsock_init();

    /* Init some protocol parser data structures */
    snmp_init();
    x509_init();


    /*
     * Apply excludes. People ask us not to scan them, so we maintain a list
     * of their ranges, and when doing wide scans, add the exclude list to
     * prevent them from being scanned.
     */
    {
        uint64_t range = rangelist_count(&masscan->targets) * rangelist_count(&masscan->ports);
        uint64_t range2;
        rangelist_exclude(&masscan->targets, &masscan->exclude_ip);
        rangelist_exclude(&masscan->ports, &masscan->exclude_port);
        //rangelist_remove_range2(&masscan->targets, range_parse_ipv4("224.0.0.0/4", 0, 0));

        range2 = rangelist_count(&masscan->targets) * rangelist_count(&masscan->ports);

        if (range != 0 && range2 == 0) {
            LOG(0, "FAIL: no ranges left to scan\n");
            LOG(0, "   ...all ranges overlapped something in an excludefile range\n");
            exit(1);
        }

        if (range2 != range && masscan->resume.index) {
            LOG(0, "FAIL: Attempted to add additional 'exclude' ranges after scan start.\n");
            LOG(0, "   ...This messes things up the scan randomization, so you have to restart scan\n");
            exit(1);
        }
    }



    /*
     * Once we've read in the configuration, do the operation that was
     * specified
     */
    switch (masscan->op) {
    case Operation_Default:
        /* Print usage info and exit */
        masscan_usage();
        break;

    case Operation_Scan:
        /*
         * THIS IS THE NORMAL THING
         */
        return main_scan(masscan);

    case Operation_ListScan:
        /* Create a randomized list of IP addresses */
        main_listscan(masscan);
        return 0;

    case Operation_List_Adapters:
        /* List the network adapters we might want to use for scanning */
        rawsock_list_adapters();
        break;

    case Operation_DebugIF:
        for (i=0; i<masscan->nic_count; i++)
            rawsock_selftest_if(masscan->nic[i].ifname);
        return 0;

    case Operation_ReadRange:
        main_readrange(masscan);
        return 0;

    case Operation_ReadScan:
        {
            unsigned start;
            unsigned stop;

            /* find first file */
            for (start=1; start<(unsigned)argc; start++) {
                if (memcmp(argv[start], "--readscan", 10) == 0) {
                    start++;
                    break;
                }
            }

            /* find last file */
            for (stop=start+1; stop<(unsigned)argc && argv[stop][0] != '-'; stop++)
                ;

            /*
             * read the binary files, and output them again depending upon
             * the output parameters
             */
            read_binary_scanfile(masscan, start, stop, argv);

        }
        break;

    case Operation_Benchmark:
        printf("=== benchmarking (%u-bits) ===\n\n", (unsigned)sizeof(void*)*8);
        blackrock_benchmark(masscan->blackrock_rounds);
        blackrock2_benchmark(masscan->blackrock_rounds);
        smack_benchmark();
        exit(1);
        break;

    case Operation_Selftest:
        /*
         * Do a regression test of all the significant units
         */
        {
            int x = 0;
            x += proto_coap_selftest();
            x += smack_selftest();
            x += sctp_selftest();
            x += base64_selftest();
            x += banner1_selftest();
            x += output_selftest();
            x += siphash24_selftest();
            x += ntp_selftest();
            x += snmp_selftest();
            x += payloads_udp_selftest();
            x += blackrock_selftest();
            x += rawsock_selftest();
            x += lcg_selftest();
            x += template_selftest();
            x += ranges_selftest();
            x += rangefile_selftest();
            x += pixie_time_selftest();
            x += rte_ring_selftest();
            x += mainconf_selftest();
            x += zeroaccess_selftest();
            x += nmapserviceprobes_selftest();
            x += rstfilter_selftest();


            if (x != 0) {
                /* one of the selftests failed, so return error */
                fprintf(stderr, "regression test: failed :( \n");
                return 1;
            } else {
                fprintf(stderr, "regression test: success!\n");
                return 0;
            }
        }
        break;
    }


    return 0;
}