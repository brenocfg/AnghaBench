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
typedef  int u32 ;

/* Variables and functions */
#define  AFSVL_BADENTRY 198 
#define  AFSVL_BADINDEX 197 
#define  AFSVL_BADNAME 196 
#define  AFSVL_BADPARTITION 195 
#define  AFSVL_BADREFCOUNT 194 
#define  AFSVL_BADRELLOCKTYPE 193 
#define  AFSVL_BADSERVER 192 
#define  AFSVL_BADSERVERFLAG 191 
#define  AFSVL_BADVOLIDBUMP 190 
#define  AFSVL_BADVOLOPER 189 
#define  AFSVL_BADVOLTYPE 188 
#define  AFSVL_CREATEFAIL 187 
#define  AFSVL_DUPREPSERVER 186 
#define  AFSVL_EMPTY 185 
#define  AFSVL_ENTDELETED 184 
#define  AFSVL_ENTRYLOCKED 183 
#define  AFSVL_IDALREADYHASHED 182 
#define  AFSVL_IDEXIST 181 
#define  AFSVL_IO 180 
#define  AFSVL_NAMEEXIST 179 
#define  AFSVL_NOENT 178 
#define  AFSVL_NOMEM 177 
#define  AFSVL_NOREPSERVER 176 
#define  AFSVL_PERM 175 
#define  AFSVL_REPSFULL 174 
#define  AFSVL_RERELEASE 173 
#define  AFSVL_RWNOTFOUND 172 
#define  AFSVL_SIZEEXCEEDED 171 
 int EACCES ; 
 int EBADRQC ; 
 int EBUSY ; 
 int EDEADLK ; 
 int EDQUOT ; 
 int EEXIST ; 
 int EFBIG ; 
 int EINVAL ; 
 int EIO ; 
 int EISDIR ; 
 int EKEYEXPIRED ; 
 int EKEYREJECTED ; 
 int ELOOP ; 
 int EMLINK ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOLCK ; 
 int ENOMEDIUM ; 
 int ENOSPC ; 
 int ENOTDIR ; 
 int ENOTEMPTY ; 
 int ENOTSUPP ; 
 int ENXIO ; 
 int EPERM ; 
 int EPROTO ; 
 int EREMOTEIO ; 
 int EROFS ; 
#define  RXGEN_OPCODE 170 
#define  RXKADBADKEY 169 
#define  RXKADBADTICKET 168 
#define  RXKADDATALEN 167 
#define  RXKADEXPIRED 166 
#define  RXKADILLEGALLEVEL 165 
#define  RXKADINCONSISTENCY 164 
#define  RXKADLEVELFAIL 163 
#define  RXKADNOAUTH 162 
#define  RXKADOUTOFSEQUENCE 161 
#define  RXKADPACKETSHORT 160 
#define  RXKADSEALEDINCON 159 
#define  RXKADTICKETLEN 158 
#define  RXKADUNKNOWNKEY 157 
#define  UAEACCES 156 
#define  UAEBUSY 155 
#define  UAEDEADLK 154 
#define  UAEDQUOT 153 
#define  UAEEXIST 152 
#define  UAEFBIG 151 
#define  UAEISDIR 150 
#define  UAELOOP 149 
#define  UAEMLINK 148 
#define  UAENAMETOOLONG 147 
#define  UAENOENT 146 
#define  UAENOLCK 145 
#define  UAENOMEDIUM 144 
#define  UAENOSPC 143 
#define  UAENOTDIR 142 
#define  UAENOTEMPTY 141 
#define  UAEPERM 140 
#define  UAEROFS 139 
#define  VBUSY 138 
#define  VDISKFULL 137 
#define  VMOVED 136 
#define  VNOSERVICE 135 
#define  VNOVNODE 134 
#define  VNOVOL 133 
#define  VOFFLINE 132 
#define  VONLINE 131 
#define  VOVERQUOTA 130 
#define  VSALVAGE 129 
#define  VVOLEXISTS 128 

int afs_abort_to_error(u32 abort_code)
{
	switch (abort_code) {
		/* Low errno codes inserted into abort namespace */
	case 13:		return -EACCES;
	case 27:		return -EFBIG;
	case 30:		return -EROFS;

		/* VICE "special error" codes; 101 - 111 */
	case VSALVAGE:		return -EIO;
	case VNOVNODE:		return -ENOENT;
	case VNOVOL:		return -ENOMEDIUM;
	case VVOLEXISTS:	return -EEXIST;
	case VNOSERVICE:	return -EIO;
	case VOFFLINE:		return -ENOENT;
	case VONLINE:		return -EEXIST;
	case VDISKFULL:		return -ENOSPC;
	case VOVERQUOTA:	return -EDQUOT;
	case VBUSY:		return -EBUSY;
	case VMOVED:		return -ENXIO;

		/* Volume Location server errors */
	case AFSVL_IDEXIST:		return -EEXIST;
	case AFSVL_IO:			return -EREMOTEIO;
	case AFSVL_NAMEEXIST:		return -EEXIST;
	case AFSVL_CREATEFAIL:		return -EREMOTEIO;
	case AFSVL_NOENT:		return -ENOMEDIUM;
	case AFSVL_EMPTY:		return -ENOMEDIUM;
	case AFSVL_ENTDELETED:		return -ENOMEDIUM;
	case AFSVL_BADNAME:		return -EINVAL;
	case AFSVL_BADINDEX:		return -EINVAL;
	case AFSVL_BADVOLTYPE:		return -EINVAL;
	case AFSVL_BADSERVER:		return -EINVAL;
	case AFSVL_BADPARTITION:	return -EINVAL;
	case AFSVL_REPSFULL:		return -EFBIG;
	case AFSVL_NOREPSERVER:		return -ENOENT;
	case AFSVL_DUPREPSERVER:	return -EEXIST;
	case AFSVL_RWNOTFOUND:		return -ENOENT;
	case AFSVL_BADREFCOUNT:		return -EINVAL;
	case AFSVL_SIZEEXCEEDED:	return -EINVAL;
	case AFSVL_BADENTRY:		return -EINVAL;
	case AFSVL_BADVOLIDBUMP:	return -EINVAL;
	case AFSVL_IDALREADYHASHED:	return -EINVAL;
	case AFSVL_ENTRYLOCKED:		return -EBUSY;
	case AFSVL_BADVOLOPER:		return -EBADRQC;
	case AFSVL_BADRELLOCKTYPE:	return -EINVAL;
	case AFSVL_RERELEASE:		return -EREMOTEIO;
	case AFSVL_BADSERVERFLAG:	return -EINVAL;
	case AFSVL_PERM:		return -EACCES;
	case AFSVL_NOMEM:		return -EREMOTEIO;

		/* Unified AFS error table */
	case UAEPERM:			return -EPERM;
	case UAENOENT:			return -ENOENT;
	case UAEACCES:			return -EACCES;
	case UAEBUSY:			return -EBUSY;
	case UAEEXIST:			return -EEXIST;
	case UAENOTDIR:			return -ENOTDIR;
	case UAEISDIR:			return -EISDIR;
	case UAEFBIG:			return -EFBIG;
	case UAENOSPC:			return -ENOSPC;
	case UAEROFS:			return -EROFS;
	case UAEMLINK:			return -EMLINK;
	case UAEDEADLK:			return -EDEADLK;
	case UAENAMETOOLONG:		return -ENAMETOOLONG;
	case UAENOLCK:			return -ENOLCK;
	case UAENOTEMPTY:		return -ENOTEMPTY;
	case UAELOOP:			return -ELOOP;
	case UAENOMEDIUM:		return -ENOMEDIUM;
	case UAEDQUOT:			return -EDQUOT;

		/* RXKAD abort codes; from include/rxrpc/packet.h.  ET "RXK" == 0x1260B00 */
	case RXKADINCONSISTENCY: return -EPROTO;
	case RXKADPACKETSHORT:	return -EPROTO;
	case RXKADLEVELFAIL:	return -EKEYREJECTED;
	case RXKADTICKETLEN:	return -EKEYREJECTED;
	case RXKADOUTOFSEQUENCE: return -EPROTO;
	case RXKADNOAUTH:	return -EKEYREJECTED;
	case RXKADBADKEY:	return -EKEYREJECTED;
	case RXKADBADTICKET:	return -EKEYREJECTED;
	case RXKADUNKNOWNKEY:	return -EKEYREJECTED;
	case RXKADEXPIRED:	return -EKEYEXPIRED;
	case RXKADSEALEDINCON:	return -EKEYREJECTED;
	case RXKADDATALEN:	return -EKEYREJECTED;
	case RXKADILLEGALLEVEL:	return -EKEYREJECTED;

	case RXGEN_OPCODE:	return -ENOTSUPP;

	default:		return -EREMOTEIO;
	}
}