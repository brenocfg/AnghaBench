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
struct PcapFunctions {int is_available; int is_printing_debug; int func_err; int /*<<< orphan*/ * activate; int /*<<< orphan*/ * can_set_rfmon; int /*<<< orphan*/ * set_rfmon; int /*<<< orphan*/ * set_buffer_size; int /*<<< orphan*/ * set_immediate_mode; int /*<<< orphan*/ * set_timeout; int /*<<< orphan*/ * set_promisc; int /*<<< orphan*/ * set_snaplen; int /*<<< orphan*/ * create; int /*<<< orphan*/  dev_next; int /*<<< orphan*/  dev_description; int /*<<< orphan*/  dev_name; int /*<<< orphan*/ * geterr; int /*<<< orphan*/ * perror; int /*<<< orphan*/ * datalink_val_to_name; int /*<<< orphan*/ * setdirection; int /*<<< orphan*/ * next; int /*<<< orphan*/ * sendpacket; int /*<<< orphan*/ * open_offline; int /*<<< orphan*/ * open_live; int /*<<< orphan*/ * minor_version; int /*<<< orphan*/ * major_version; int /*<<< orphan*/ * lookupdev; int /*<<< orphan*/ * lib_version; int /*<<< orphan*/ * freealldevs; int /*<<< orphan*/ * findalldevs; int /*<<< orphan*/ * dispatch; int /*<<< orphan*/ * datalink; int /*<<< orphan*/ * close; } ;
typedef  int /*<<< orphan*/ * PCAP_SET_TIMEOUT ;
typedef  int /*<<< orphan*/ * PCAP_SET_SNAPLEN ;
typedef  int /*<<< orphan*/ * PCAP_SET_RFMON ;
typedef  int /*<<< orphan*/ * PCAP_SET_PROMISC ;
typedef  int /*<<< orphan*/ * PCAP_SET_IMMEDIATE_MODE ;
typedef  int /*<<< orphan*/ * PCAP_SET_BUFFER_SIZE ;
typedef  int /*<<< orphan*/ * PCAP_SETDIRECTION ;
typedef  int /*<<< orphan*/ * PCAP_SENDPACKET ;
typedef  int /*<<< orphan*/ * PCAP_PERROR ;
typedef  int /*<<< orphan*/ * PCAP_OPEN_OFFLINE ;
typedef  int /*<<< orphan*/ * PCAP_OPEN_LIVE ;
typedef  int /*<<< orphan*/ * PCAP_NEXT ;
typedef  int /*<<< orphan*/ * PCAP_MINOR_VERSION ;
typedef  int /*<<< orphan*/ * PCAP_MAJOR_VERSION ;
typedef  int /*<<< orphan*/ * PCAP_LOOKUPDEV ;
typedef  int /*<<< orphan*/ * PCAP_LIB_VERSION ;
typedef  int /*<<< orphan*/ * PCAP_GETERR ;
typedef  int /*<<< orphan*/ * PCAP_FREEALLDEVS ;
typedef  int /*<<< orphan*/ * PCAP_FINDALLDEVS ;
typedef  int /*<<< orphan*/ * PCAP_DISPATCH ;
typedef  int /*<<< orphan*/ * PCAP_DATALINK_VAL_TO_NAME ;
typedef  int /*<<< orphan*/ * PCAP_DATALINK ;
typedef  int /*<<< orphan*/ * PCAP_CREATE ;
typedef  int /*<<< orphan*/ * PCAP_CLOSE ;
typedef  int /*<<< orphan*/ * PCAP_CAN_SET_RFMON ;
typedef  int /*<<< orphan*/ * PCAP_ACTIVATE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int,char*,char const*) ; 
 struct PcapFunctions PCAP ; 
 int /*<<< orphan*/  RTLD_LAZY ; 
 void* dlopen (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ dlsym (void*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * null_PCAP_ACTIVATE ; 
 int /*<<< orphan*/ * null_PCAP_CAN_SET_RFMON ; 
 int /*<<< orphan*/ * null_PCAP_CLOSE ; 
 int /*<<< orphan*/ * null_PCAP_CREATE ; 
 int /*<<< orphan*/ * null_PCAP_DATALINK ; 
 int /*<<< orphan*/ * null_PCAP_DATALINK_VAL_TO_NAME ; 
 int /*<<< orphan*/  null_PCAP_DEV_DESCRIPTION ; 
 int /*<<< orphan*/  null_PCAP_DEV_NAME ; 
 int /*<<< orphan*/  null_PCAP_DEV_NEXT ; 
 int /*<<< orphan*/ * null_PCAP_DISPATCH ; 
 int /*<<< orphan*/ * null_PCAP_FINDALLDEVS ; 
 int /*<<< orphan*/ * null_PCAP_FREEALLDEVS ; 
 int /*<<< orphan*/ * null_PCAP_GETERR ; 
 int /*<<< orphan*/ * null_PCAP_LIB_VERSION ; 
 int /*<<< orphan*/ * null_PCAP_LOOKUPDEV ; 
 int /*<<< orphan*/ * null_PCAP_MAJOR_VERSION ; 
 int /*<<< orphan*/ * null_PCAP_MINOR_VERSION ; 
 int /*<<< orphan*/ * null_PCAP_NEXT ; 
 int /*<<< orphan*/ * null_PCAP_OPEN_LIVE ; 
 int /*<<< orphan*/ * null_PCAP_OPEN_OFFLINE ; 
 int /*<<< orphan*/ * null_PCAP_PERROR ; 
 int /*<<< orphan*/ * null_PCAP_SENDPACKET ; 
 int /*<<< orphan*/ * null_PCAP_SETDIRECTION ; 
 int /*<<< orphan*/ * null_PCAP_SET_BUFFER_SIZE ; 
 int /*<<< orphan*/ * null_PCAP_SET_IMMEDIATE_MODE ; 
 int /*<<< orphan*/ * null_PCAP_SET_PROMISC ; 
 int /*<<< orphan*/ * null_PCAP_SET_RFMON ; 
 int /*<<< orphan*/ * null_PCAP_SET_SNAPLEN ; 
 int /*<<< orphan*/ * null_PCAP_SET_TIMEOUT ; 
 int /*<<< orphan*/  stderr ; 

int pcap_init(void)
{
    struct PcapFunctions *pl = &PCAP;
#ifdef WIN32
    void * hPacket;
    void * hLibpcap;
    
    pl->is_available = 0;
    pl->is_printing_debug = 1;
    
    /* Look for the Packet.dll */
    hPacket = LoadLibraryA("NPcap\\Packet.dll");
    if (hPacket == NULL)
        hPacket = LoadLibraryA("Packet.dll");
    if (hPacket == NULL) {
        if (pl->is_printing_debug)
        switch (GetLastError()) {
            case ERROR_MOD_NOT_FOUND:
                fprintf(stderr, "%s: not found\n", "Packet.dll");
                fprintf(stderr, "  HINT: you must install either WinPcap or Npcap\n");
                return -1;
            default:
                fprintf(stderr, "%s: couldn't load %d\n", "Packet.dll", (int)GetLastError());
                return -1;
        }
    }
    
    /* Look for the winpcap.dll */
    hLibpcap = LoadLibraryA("Npcap\\wpcap.dll");
    if (hLibpcap == NULL)
        hLibpcap = LoadLibraryA("wpcap.dll");
    if (hLibpcap == NULL) {
        if (pl->is_printing_debug)
            fprintf(stderr, "%s: couldn't load %d\n", "wpcap.dll", (int)GetLastError());
        return -1;
    }
    
    
#define DOLINK(PCAP_DATALINK, datalink) \
pl->datalink = (PCAP_DATALINK)GetProcAddress(hLibpcap, "pcap_"#datalink); \
if (pl->datalink == NULL) pl->func_err=1, pl->datalink = null_##PCAP_DATALINK;
#endif
    
    
#ifndef WIN32
#ifndef STATICPCAP
    void *hLibpcap;
    
    pl->is_available = 0;
    pl->is_printing_debug = 1;
    
    {
        static const char *possible_names[] = {
            "libpcap.so",
            "libpcap.A.dylib",
            "libpcap.dylib",
            "libpcap.so.0.9.5",
            "libpcap.so.0.9.4",
            "libpcap.so.0.8",
            0
        };
        unsigned i;
        for (i=0; possible_names[i]; i++) {
            hLibpcap = dlopen(possible_names[i], RTLD_LAZY);
            if (hLibpcap) {
                LOG(1, "pcap: found library: %s\n", possible_names[i]);
                break;
            } else {
                LOG(2, "pcap: failed to load: %s\n", possible_names[i]);
            }
        }
     
        if (hLibpcap == NULL) {
            fprintf(stderr, "pcap: failed to load libpcap shared library\n");
            fprintf(stderr, "    HINT: you must install libpcap or WinPcap\n");
        }
    }
    
#define DOLINK(PCAP_DATALINK, datalink) \
pl->datalink = (PCAP_DATALINK)dlsym(hLibpcap, "pcap_"#datalink); \
    if (pl->datalink == NULL) LOG(1, "pcap: pcap_%s: failed\n", #datalink); \
    if (pl->datalink == NULL) pl->func_err=1, pl->datalink = null_##PCAP_DATALINK;
#else
#define DOLINK(PCAP_DATALINK, datalink) \
pl->func_err=0, pl->datalink = null_##PCAP_DATALINK;
#endif
#endif
    
    DOLINK(PCAP_CLOSE			, close);
    DOLINK(PCAP_DATALINK		, datalink);
    DOLINK(PCAP_DISPATCH		, dispatch);
    DOLINK(PCAP_FINDALLDEVS		, findalldevs);
    DOLINK(PCAP_FREEALLDEVS		, freealldevs);
    DOLINK(PCAP_LIB_VERSION		, lib_version);
    DOLINK(PCAP_LOOKUPDEV		, lookupdev);
    DOLINK(PCAP_MAJOR_VERSION	, major_version);
    DOLINK(PCAP_MINOR_VERSION	, minor_version);
    DOLINK(PCAP_OPEN_LIVE		, open_live);
    
    DOLINK(PCAP_OPEN_OFFLINE    , open_offline);
    DOLINK(PCAP_SENDPACKET      , sendpacket);
    DOLINK(PCAP_NEXT            , next);
    DOLINK(PCAP_SETDIRECTION    , setdirection);
    DOLINK(PCAP_DATALINK_VAL_TO_NAME , datalink_val_to_name);
    DOLINK(PCAP_PERROR          , perror);
    DOLINK(PCAP_GETERR          , geterr);


    /* pseudo functions that don't exist in the libpcap interface */
    pl->dev_name = null_PCAP_DEV_NAME;
    pl->dev_description = null_PCAP_DEV_DESCRIPTION;
    pl->dev_next = null_PCAP_DEV_NEXT;

    /* windows-only functions that might improve speed */
#if defined(WIN32)
	DOLINK(PCAP_SENDQUEUE_ALLOC		, sendqueue_alloc);
	DOLINK(PCAP_SENDQUEUE_TRANSMIT	, sendqueue_transmit);
	DOLINK(PCAP_SENDQUEUE_DESTROY	, sendqueue_destroy);
	DOLINK(PCAP_SENDQUEUE_QUEUE		, sendqueue_queue);
#endif

    DOLINK(PCAP_CREATE              , create);
    DOLINK(PCAP_SET_SNAPLEN         , set_snaplen);
    DOLINK(PCAP_SET_PROMISC         , set_promisc);
    DOLINK(PCAP_SET_TIMEOUT         , set_timeout);
    DOLINK(PCAP_SET_IMMEDIATE_MODE  , set_immediate_mode);
    DOLINK(PCAP_SET_BUFFER_SIZE     , set_buffer_size);
    DOLINK(PCAP_SET_RFMON           , set_rfmon);
    DOLINK(PCAP_CAN_SET_RFMON       , can_set_rfmon);
    DOLINK(PCAP_ACTIVATE            , activate);

    
    if (!pl->func_err)
        pl->is_available = 1;
    else
        pl->is_available = 0;
    
    return 0;
}