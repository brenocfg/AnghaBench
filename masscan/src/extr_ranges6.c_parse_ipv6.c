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
typedef  unsigned long long uint64_t ;
struct TYPE_3__ {unsigned long long hi; unsigned long long lo; } ;
typedef  TYPE_1__ ipv6address ;

/* Variables and functions */
 unsigned int hexval (char const) ; 
 scalar_t__ isdigit (char const) ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  isxdigit (char const) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 unsigned char prefix_length ; 

__attribute__((used)) static int
parse_ipv6(const char *buf, unsigned *offset, size_t length, ipv6address *ip)
{
	unsigned i = *offset;
	unsigned is_bracket_seen = 0;
	unsigned elision_offset = (unsigned)~0;
	unsigned d = 0;
    //unsigned prefix_length = 128;
    unsigned char address[16];

    /* If no /CIDR spec is found, assume 128-bits for IPv6 addresses */
    //prefix_length = 128;

	/* Remove leading whitespace */
	while (i < length && isspace(buf[i]))
		i++;

	/* If the address starts with a '[', then remove it */
	if (i < length && buf[i] == '[') {
		is_bracket_seen = 1;
		i++;

        /* remove more whitespace */
		while (i < length && isspace(buf[i]))
			i++;
	}

	/* Now parse all the numbers out of the stream */
	while (i < length) {
		unsigned j;
		unsigned number = 0;

		/* Have we found all 128-bits/16-bytes? */
		if (d >= 16)
			break;

		/* Is there an elision/compression of the address? */
		if (buf[i] == ':' && elision_offset < 16) {
			elision_offset = d;
			i++;
			continue;
		}

		/* Parse the hex digits into a 2-byte number */
		j=0;
		while (i < length) {
			if (j >= 4)
				break; /* max 4 hex digits at a time */
			if (buf[i] == ':')
				break; /* early exit due to leading nuls */
			if (!isxdigit(buf[i])) {
				break; /* error */
			}

			number <<= 4;
			number |= hexval(buf[i++]);
			j++;
		}

		/* If no hex digits were processed */
		if (j == 0)
			break;

		/* We have a 2-byte number */
		address[d+0] = (unsigned char)(number>>8);
		address[d+1] = (unsigned char)(number>>0);
		d += 2;

		/* See if we have the normal continuation */
		if (i < length && buf[i] == ':') {
			i++;
			continue;
		}

		/* Or, see if we have reached the trailing ']' character */
		if (i < length && is_bracket_seen && buf[i] == ']') {
			i++; /* skip ']' */
			//is_bracket_seen = false;
			break;
		}

		/* We have parsed all the address we are looking for. Therefore, stop
		 * parsing at this point */
		if (d == 16)
			break;

		/* Is there an ellision in this address? If so, break at this point */
		if (elision_offset != (unsigned)(~0))
			break;

		/* See if we have reached the end of the address. */
		if (i == length)
			break;

		/* Some unknown character is seen, therefore return an
		 * error */
		return -1;
	}

	/* Insert zeroes where numbers were removed */
	if (elision_offset != ~0) {
		if (d == 16) {
			/* oops, there was no elision, this is an error */
			return -1;
		}

		memmove(address + elision_offset + 16 - d, 
				address + elision_offset,
				d - elision_offset);
		memset(	address + elision_offset,
				0,
				16-d);
	}

#if 0
    /* Check for optional CIDR field */
    if (i < length && buf[i] == '/') {
        unsigned n = 0;
        
        i++;

        if (i >= length || !isdigit(buf[i]))
            return -1;

        n = buf[i] - '0';
        i++;

        if (i<length && isdigit(buf[i])) {
            n = n * 10 + buf[i] - '0';
            i++;
        }

        if (n > 128)
            return -1;
        else
            prefix_length = (unsigned char)n;
    }
#endif

    ip->hi =    (((uint64_t)address[0]) << 56ULL)
                    | ((uint64_t)address[1] << 48ULL)
                    | ((uint64_t)address[2] << 40ULL)
                    | ((uint64_t)address[3] << 32ULL)
                    | ((uint64_t)address[4] << 24ULL)
                    | ((uint64_t)address[5] << 16ULL)
                    | ((uint64_t)address[6] <<  8ULL)
                    | ((uint64_t)address[7] <<  0ULL);
    ip->lo =    ((uint64_t)address[ 8] << 56ULL)
                    | ((uint64_t)address[ 9] << 48ULL)
                    | ((uint64_t)address[10] << 40ULL)
                    | ((uint64_t)address[11] << 32ULL)
                    | ((uint64_t)address[12] << 24ULL)
                    | ((uint64_t)address[13] << 16ULL)
                    | ((uint64_t)address[14] <<  8ULL)
                    | ((uint64_t)address[15] <<  0ULL);
    
    *offset = i;

    /* Now convert the prefix into a begin/end */
    {
        //ip->hi = address[0]<<56ULL;

    }
    return true;
}