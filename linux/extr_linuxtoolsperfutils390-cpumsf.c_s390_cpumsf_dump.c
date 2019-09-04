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
typedef  int /*<<< orphan*/  te ;
struct s390_cpumsf {int /*<<< orphan*/  machine_type; } ;
struct hws_trailer_entry {unsigned short bsdes; unsigned short dsdes; } ;
struct hws_diag_entry {int dummy; } ;
struct hws_basic_entry {int dummy; } ;

/* Variables and functions */
 char* PERF_COLOR_BLUE ; 
 size_t S390_CPUMSF_PAGESZ ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,char const*,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (struct hws_trailer_entry*,unsigned char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,size_t,int /*<<< orphan*/ ,unsigned short,unsigned short) ; 
 scalar_t__ s390_cpumsf_basic_show (char const*,size_t,struct hws_basic_entry*) ; 
 scalar_t__ s390_cpumsf_diag_show (char const*,size_t,struct hws_diag_entry*) ; 
 int /*<<< orphan*/  s390_cpumsf_reached_trailer (unsigned short,size_t) ; 
 scalar_t__ s390_cpumsf_trailer_show (char const*,size_t,struct hws_trailer_entry*) ; 
 int /*<<< orphan*/  s390_cpumsf_validate (int /*<<< orphan*/ ,unsigned char*,size_t,unsigned short*,unsigned short*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void s390_cpumsf_dump(struct s390_cpumsf *sf,
			     unsigned char *buf, size_t len)
{
	const char *color = PERF_COLOR_BLUE;
	struct hws_basic_entry *basic;
	struct hws_diag_entry *diag;
	unsigned short bsdes, dsdes;
	size_t pos = 0;

	color_fprintf(stdout, color,
		      ". ... s390 AUX data: size %zu bytes\n",
		      len);

	if (!s390_cpumsf_validate(sf->machine_type, buf, len, &bsdes,
				  &dsdes)) {
		pr_err("Invalid AUX trace data block size:%zu"
		       " (type:%d bsdes:%hd dsdes:%hd)\n",
		       len, sf->machine_type, bsdes, dsdes);
		return;
	}

	/* s390 kernel always returns 4KB blocks fully occupied,
	 * no partially filled SDBs.
	 */
	while (pos < len) {
		/* Handle Basic entry */
		basic = (struct hws_basic_entry *)(buf + pos);
		if (s390_cpumsf_basic_show(color, pos, basic))
			pos += bsdes;
		else
			return;

		/* Handle Diagnostic entry */
		diag = (struct hws_diag_entry *)(buf + pos);
		if (s390_cpumsf_diag_show(color, pos, diag))
			pos += dsdes;
		else
			return;

		/* Check for trailer entry */
		if (!s390_cpumsf_reached_trailer(bsdes + dsdes, pos)) {
			/* Show trailer entry */
			struct hws_trailer_entry te;

			pos = (pos + S390_CPUMSF_PAGESZ)
			       & ~(S390_CPUMSF_PAGESZ - 1);
			pos -= sizeof(te);
			memcpy(&te, buf + pos, sizeof(te));
			/* Set descriptor sizes in case of old hardware
			 * where these values are not set.
			 */
			te.bsdes = bsdes;
			te.dsdes = dsdes;
			if (s390_cpumsf_trailer_show(color, pos, &te))
				pos += sizeof(te);
			else
				return;
		}
	}
}