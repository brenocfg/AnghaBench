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
struct super_block {int dummy; } ;
struct adfs_sb_info {unsigned int s_map_size; unsigned int s_ids_per_zone; int s_idlen; int /*<<< orphan*/  s_map2blk; } ;
struct adfs_discrecord {int log2secsize; unsigned int log2bpmb; int /*<<< orphan*/  zone_spare; } ;
struct adfs_discmap {unsigned int dm_startbit; unsigned int dm_endbit; int dm_startblk; int /*<<< orphan*/  dm_bh; } ;

/* Variables and functions */
 unsigned int ADFS_DR_SIZE_BITS ; 
 struct adfs_sb_info* ADFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct adfs_discmap* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ adfs_checkmap (struct super_block*,struct adfs_discmap*) ; 
 unsigned int adfs_disc_size (struct adfs_discrecord*) ; 
 int /*<<< orphan*/  adfs_error (struct super_block*,char*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct adfs_discmap*) ; 
 struct adfs_discmap* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_bread (struct super_block*,unsigned int) ; 
 unsigned int signed_asl (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct adfs_discmap *adfs_read_map(struct super_block *sb, struct adfs_discrecord *dr)
{
	struct adfs_discmap *dm;
	unsigned int map_addr, zone_size, nzones;
	int i, zone;
	struct adfs_sb_info *asb = ADFS_SB(sb);

	nzones    = asb->s_map_size;
	zone_size = (8 << dr->log2secsize) - le16_to_cpu(dr->zone_spare);
	map_addr  = (nzones >> 1) * zone_size -
		     ((nzones > 1) ? ADFS_DR_SIZE_BITS : 0);
	map_addr  = signed_asl(map_addr, asb->s_map2blk);

	asb->s_ids_per_zone = zone_size / (asb->s_idlen + 1);

	dm = kmalloc_array(nzones, sizeof(*dm), GFP_KERNEL);
	if (dm == NULL) {
		adfs_error(sb, "not enough memory");
		return ERR_PTR(-ENOMEM);
	}

	for (zone = 0; zone < nzones; zone++, map_addr++) {
		dm[zone].dm_startbit = 0;
		dm[zone].dm_endbit   = zone_size;
		dm[zone].dm_startblk = zone * zone_size - ADFS_DR_SIZE_BITS;
		dm[zone].dm_bh       = sb_bread(sb, map_addr);

		if (!dm[zone].dm_bh) {
			adfs_error(sb, "unable to read map");
			goto error_free;
		}
	}

	/* adjust the limits for the first and last map zones */
	i = zone - 1;
	dm[0].dm_startblk = 0;
	dm[0].dm_startbit = ADFS_DR_SIZE_BITS;
	dm[i].dm_endbit   = (adfs_disc_size(dr) >> dr->log2bpmb) +
			    (ADFS_DR_SIZE_BITS - i * zone_size);

	if (adfs_checkmap(sb, dm))
		return dm;

	adfs_error(sb, "map corrupted");

error_free:
	while (--zone >= 0)
		brelse(dm[zone].dm_bh);

	kfree(dm);
	return ERR_PTR(-EIO);
}