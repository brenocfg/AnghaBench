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
typedef  int /*<<< orphan*/  pstate ;

/* Variables and functions */
 int /*<<< orphan*/  PROTO_TELNET ; 
 struct Banner1* banner1_create () ; 
 int /*<<< orphan*/  banner1_destroy (struct Banner1*) ; 
 int /*<<< orphan*/  banout_init (struct BannerOutput*) ; 
 int banout_is_contains (struct BannerOutput*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  banout_release (struct BannerOutput*) ; 
 int /*<<< orphan*/  memset (struct ProtocolState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  telnet_parse (struct Banner1*,int /*<<< orphan*/ ,struct ProtocolState*,unsigned char const*,int /*<<< orphan*/ ,struct BannerOutput*,struct InteractiveData*) ; 

__attribute__((used)) static int
telnet_selftest_item(const char *input, const char *output)
{
    struct Banner1 *banner1;
    struct ProtocolState pstate[1];
    struct BannerOutput banout1[1];
    struct InteractiveData more;
    int x;
    
    /*
     * Initiate a pseudo-environment for the parser
     */
    banner1 = banner1_create();
    banout_init(banout1);
    memset(&pstate[0], 0, sizeof(pstate[0]));
    
    /*
     * Parse the input payload
     */
    telnet_parse(banner1,
                 0,
                 pstate,
                 (const unsigned char *)input,
                 strlen(input),
                 banout1,
                 &more
                 );
    //fprintf(stderr, "%.*s\n", (int)banout_string_length(banout1, PROTO_TELNET), banout_string(banout1, PROTO_TELNET));
    /*
     * Verify that somewhere in the output is the string
     * we are looking for
     */
    x = banout_is_contains(banout1, PROTO_TELNET, output);
    if (x == 0)
        printf("telnet parser failure: %s\n", output);
    banner1_destroy(banner1);
    banout_release(banout1);
    
    return (x==0)?1:0;
}