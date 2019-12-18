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
struct ProtocolState {int dummy; } ;
struct InteractiveData {int dummy; } ;
struct BannerOutput {int dummy; } ;
struct Banner1 {int dummy; } ;
typedef  int /*<<< orphan*/  state ;

/* Variables and functions */
 int /*<<< orphan*/  PROTO_SMB ; 
 struct Banner1* banner1_create () ; 
 int /*<<< orphan*/  banner1_destroy (struct Banner1*) ; 
 int /*<<< orphan*/  banout_init (struct BannerOutput*) ; 
 int banout_is_contains (struct BannerOutput*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  banout_release (struct BannerOutput*) ; 
 int /*<<< orphan*/  memset (struct ProtocolState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  smb_parse_record (struct Banner1*,int /*<<< orphan*/ ,struct ProtocolState*,unsigned char const*,size_t,struct BannerOutput*,struct InteractiveData*) ; 

__attribute__((used)) static int
smb_do_test(const char *substring, const unsigned char *packet_bytes, size_t length)
{
    struct Banner1 *banner1;
    struct ProtocolState state[1];
    struct BannerOutput banout1[1];
    struct InteractiveData more;
    int x;
    
    banner1 = banner1_create();
    banout_init(banout1);
    memset(&state[0], 0, sizeof(state[0]));
    
    smb_parse_record(banner1,
                     0,
                     state,
                     packet_bytes,
                     length,
                     banout1,
                     &more);
    x = banout_is_contains(banout1, PROTO_SMB, substring);
    if (x == 0)
        printf("smb parser failure: %s\n", substring);
    banner1_destroy(banner1);
    banout_release(banout1);
    
    return x?0:1;
}