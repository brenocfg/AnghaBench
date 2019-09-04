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
struct CoapLink {int dummy; } ;
struct BannerOutput {int dummy; } ;
typedef  int /*<<< orphan*/  input ;

/* Variables and functions */
 int /*<<< orphan*/  PROTO_COAP ; 
 int /*<<< orphan*/  banout_init (struct BannerOutput*) ; 
 int /*<<< orphan*/  banout_release (struct BannerOutput*) ; 
 unsigned char* banout_string (struct BannerOutput*,int /*<<< orphan*/ ) ; 
 size_t banout_string_length (struct BannerOutput*,int /*<<< orphan*/ ) ; 
 int coap_parse (unsigned char const*,int,struct BannerOutput*,unsigned int*) ; 
 scalar_t__ memcmp (unsigned char const*,char*,int) ; 
 struct CoapLink* parse_links (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  test_is_link (char*,unsigned char const*,struct CoapLink*,size_t,int) ; 

int
proto_coap_selftest(void)
{
    
    
    struct CoapLink *links;
    size_t count=0;

    /* test quoted */
    {
        static const unsigned char *input = (const unsigned char *)
        "</sensors/temp>;if=\"se\\\"\\;\\,\\<\\>\\\\nsor\",</success>";
        links = parse_links(input, 0, (~0), &count);
        if (!test_is_link("/success", input, links, count, __LINE__))
            return 1;
    }

    /* test a simple link */
    {
        static const unsigned char *input = (const unsigned char *)
            "</sensors/temp>;if=\"sensor\"";
        links = parse_links(input, 0, (~0), &count);
        if (!test_is_link("/sensors/temp", input, links, count, __LINE__))
            return 1;
    }


    /* Test a complex dump */
    {
        static const unsigned char *input = (const unsigned char *)
            "</sensors/temp>;if=\"sensor\","
            "</sensors/light>;if=\"sensor\","
            "</sensors>;ct=40,"
            "</sensors/temp>;rt=\"temperature-c\";if=\"sensor\","
            "</sensors/light>;rt=\"light-lux\";if=\"sensor\","
            "</sensors/light>;rt=\"light-lux\";if=\"sensor\","
            "</sensors/light>;rt=\"light-lux core.sen-light\";if=\"sensor\","
            "</sensors>;ct=40;title=\"Sensor Index\","
            "</sensors/temp>;rt=\"temperature-c\";if=\"sensor\","
            "</sensors/light>;rt=\"light-lux\";if=\"sensor\","
            "<http://www.example.com/sensors/t123>;anchor=\"/sensors/temp\";rel=\"describedby\","
            "</t>;anchor=\"/sensors/temp\";rel=\"alternate\","
            "</firmware/v2.1>;rt=\"firmware\";sz=262144"
            ;
        links = parse_links(input, 0, (~0), &count);
        if (!test_is_link("/firmware/v2.1", input, links, count, __LINE__))
            return 1;
    }
    
    /* Now test an entire packet */
    {
        const char input[] =
            "\x60\x45\x01\xce\xc1\x28\xff\x3c\x2f\x72\x65\x67\x69\x73\x74\x65"
            "\x72\x3e\x2c\x3c\x2f\x6e\x64\x6d\x2f\x64\x69\x73\x3e\x2c\x3c\x2f"
            "\x6e\x64\x6d\x2f\x63\x69\x3e\x2c\x3c\x2f\x6d\x69\x72\x72\x6f\x72"
            "\x3e\x2c\x3c\x2f\x75\x68\x70\x3e\x2c\x3c\x2f\x6e\x64\x6d\x2f\x6c"
            "\x6f\x67\x6f\x75\x74\x3e\x2c\x3c\x2f\x6e\x64\x6d\x2f\x6c\x6f\x67"
            "\x69\x6e\x3e\x2c\x3c\x2f\x69\x6e\x66\x6f\x3e";
        unsigned request_id = 0;
        struct BannerOutput banout[1];
        bool is_valid;
        banout_init(banout);
        
        /* parse a test packet */
        is_valid = coap_parse( (const unsigned char*)input,
                   sizeof(input)-1,
                   banout,
                   &request_id
                   );
        //fprintf(stderr, "[+] %.*s\n", (int)banout_string_length(banout, PROTO_COAP), banout_string(banout, PROTO_COAP));
        
        if (!is_valid)
            return 1;
        if (request_id != 462)
            return 1;
        
        {
            const unsigned char *str = banout_string(banout, PROTO_COAP);
            size_t str_length = banout_string_length(banout, PROTO_COAP);
            if (str_length <= 16 && memcmp(str, "rsp=2.5(Content)", 16) != 0)
                return 1;
        }
        
        banout_release(banout);

    }
    
    return 0;
}